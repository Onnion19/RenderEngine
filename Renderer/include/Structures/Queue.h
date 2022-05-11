#pragma once 
#include "Core/types.h"
#include <optional>
#include <array>
#include "Core/RenderAssert.h"

/**
* Queue iterators will get invalidated when the queue itself changes, due to the mMax will be different so won't compute properly.
*/
template<class T>
struct QueueIterator {
	QueueIterator(T* origin, uint32 index, uint32 max) noexcept : mData(origin), mIndex(index), mMax(max) {}
	QueueIterator(const QueueIterator&)noexcept = default;
	QueueIterator& operator=(const QueueIterator&) noexcept = default;

	 QueueIterator(QueueIterator&& o)noexcept {
		mIndex = o.mIndex;
		mMax = o.mMax;
		o.mData = nullptr;
	}

	 QueueIterator& operator=(QueueIterator&& o)noexcept {
		mIndex = o.mIndex;
		mMax = o.mMax;
		o.mData = nullptr;
	}

	QueueIterator& operator++() noexcept
	{
		index = (index + 1) % mMax;
		return *this;
	}

	QueueIterator& operator--() noexcept
	{
		index = std::min(mMax, index - 1);
		return *this;
	}

	[[nodiscard]] T* get()const noexcept { return mData + mIndex; }
	[[nodiscard]] T* operator-> ()const noexcept { return mData + mIndex; }
	[[nodiscard]] const T& operator* ()const { return *(mData + mIndex); }
	[[nodiscard]] T& operator* () { return *(mData + mIndex); }

	bool operator== (const QueueIterator<T>& other) noexcept {
		return mIndex == other.mIndex && mData == other.mData;
	}

	bool operator!= (const QueueIterator<T>& other) noexcept {
		return mIndex != other.mIndex || mData != other.mData;
	}

private:
	T* mData;
	uint32 mIndex;
	uint32 mMax;

};


/*
	Implementation of a Circular queue for performance. Due to that, iterators might get invalidated
*/

template<class T, int32 Size>
class Queue {

public:
	using type = T;
	using indice = uint32;
	using iterator = QueueIterator<T>;

	/*Default constructor*/
	constexpr Queue() noexcept : mItems(0), mBegin(0), mEnd(0) { CheckForDefaultConstructor(); }

	/*Fill constructor*/
	template<class ... Args>
	constexpr Queue(uint32 nItems, Args&& ... args) noexcept {
		CheckForDefaultConstructor();
		if (nItems <= Size)
		{
			T t(std::forward<Args>(args)...);
			for(uint32 i = 0; i < nItems; i++)
				memcpy(&mArray[i], &t, sizeof(T));
			mItems = nItems;
			mBegin = 0;
			mEnd = mItems-1;
		}
	}

	template<class ... Args>
	std::optional<QueueIterator<T>> SafeEnqueue(Args && ... args) noexcept {
		if (HasSpace())
		{
			mArray[mEnd] = T(std::forward<Args>(args)...);
			mItems++;
			const iterator iter(mArray, mEnd, mItems);
			mEnd = GetNextIndice(mEnd);
			return iter;
		}
		return std::nullopt;
	}

	template<class ... Args>
	QueueIterator<T> UnsafeEnqueue(Args && ... args) noexcept {
		RenderAsssert::Test(HasSpace(), "Queue's space is full");
		mArray[mEnd] = T(std::forward<Args>(args)...);
		auto t = T(std::forward<Args>(args)...);
		mItems = mItems+1;
		const iterator iter(mArray, mEnd, mItems);
		mEnd = GetNextIndice(mEnd);
		return iter;
	}

	[[nodiscard]]std::optional<T> SafeDequeue() {
		if (mItems)
		{
			T item = mArray[mBegin];
			mArray[mBegin] = T();
			mBegin = GetNextIndice(mBegin);
			mItems--;
			return std::move(item);
		}
		return std::nullopt;
	}

	[[nodiscard]]T&& UnsafeDequeue() {
		RenderAsssert::Test(mItems, "Queue is Empty, can't dequeue");
		T item = mArray[mBegin];
		mArray[mBegin] = {};
		mBegin = GetNextIndice(mBegin);
		mItems--;
		return std::move<item>;
	}

	[[nodiscard]] constexpr int32 MaxSize()const noexcept { return Size; }
	[[nodiscard]] int32 GetSize()const noexcept { return mItems; }

	void Clear() {
		T t();
		memset(mArray, static_cast<unsigned char>(t), Size - 1);//I think this won't call the destructor ... 
		mItems = mBegin = mEnd = 0;
	}

	[[nodiscard]] iterator Front() noexcept { return iterator(mArray, mBegin, mItems); }
	[[nodiscard]] iterator Begin() noexcept { return Front(); }
	[[nodiscard]] iterator End() noexcept { return iterator(mArray, mEnd, mItems); }


private:

	constexpr void CheckForDefaultConstructor() { static_assert(std::is_constructible<T>::value, "Queue requires a type to be default constructible"); }

	[[nodiscard]] bool HasSpace() const noexcept { return mItems < Size; }
	[[nodiscard]] indice GetNextIndice(indice from)const noexcept { return (from + 1) % Size; }

private:
	T mArray[Size];
	indice mItems;
	indice mBegin;
	indice mEnd;
};