#pragma once 

#include <functional>
#include <memory>


namespace Renderer::Core {

	/*
	* @brief observer pointer implementation
	* Observers are just a wrappers of raw pointers, the strong point 
	* of them are the fact that they guarantee the ownership of the pointer
	* because it can't be deleted.
	*/
	template<class T>
	struct ObserverHandler {
		

		ObserverHandler() : mPtr(nullptr) {}
		ObserverHandler(T* ref) : mPtr(ref) {}
		explicit ObserverHandler(const std::unique_ptr<T>& handler) : mPtr(handler.get()) {}
		explicit ObserverHandler(const ObserverHandler&) noexcept = default;
		ObserverHandler& operator=(const ObserverHandler&) noexcept = default;
		
		ObserverHandler(ObserverHandler&& o) noexcept {
			mPtr = o.mPtr;
			o.mPtr = nullptr;
		}
		ObserverHandler& operator =(ObserverHandler&& o) noexcept {
			mPtr = o.mPtr;
			o.mPtr = nullptr;
			return *this;
		}

		[[nodiscard]] bool Valid()const { return mPtr; }
		void release() { mPtr = nullptr; }
		void reset(T* ref) { mPtr = ref; }

		[[nodiscard]] T* operator->()const { return mPtr; }
		[[nodiscard]] T* get()const { return mPtr; }
		operator T*() {return mPtr; }

	private: 
		T* mPtr;
	};

	template<class T>
	constexpr ObserverHandler<T> MakeObserver(T* ref)
	{
		return ObserverHandler<T>(ref);
	}

}