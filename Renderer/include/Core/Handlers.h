#pragma once 

#include <functional>
#include <memory>


namespace Renderer::Core {


	template<class T>
	struct ObserverHandler {
		

		ObserverHandler() : mPtr(nullptr) {}
		explicit ObserverHandler(T* ref) : mPtr(ref) {}
		explicit ObserverHandler(const std::unique_ptr<T>& handler) : mPtr(handler.get()) {}
		explicit ObserverHandler(const ObserverHandler&) = default;
		ObserverHandler& operator=(const ObserverHandler&) = default;
		
		ObserverHandler(ObserverHandler&&) = delete;
		ObserverHandler& operator =(ObserverHandler&&) = delete;

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