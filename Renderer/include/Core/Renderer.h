#pragma once 

#include "Core/types.h"
#include <unordered_map>
#include <any>
#include "Core/RenderAssert.h"
#include <optional>

namespace Renderer
{
	/*
		I HATE TO DO THIS KIND OF GLOBAL STUFF ONLY DUE TO
		GLFW IS BASED IN FREE FUNCTIONS AND CAN'T BIND OBJECT MEMBER FUNCS.
	*/


	namespace Internal {
		template<class T>
		void Adress() {}
	}

	class GlobalRenderer {

	public:

		GlobalRenderer* Get() {
			if (!instance)
				instance = new GlobalRenderer();
			return instance; 
		}

		template<class T, class ... Args>
		void CreateSystem(Args&& ... args) {
			std::intptr_t adress = reinterpret_cast<std::intptr_t>(Internal::Adress<T>);
			RenderAsssert::Test(mSystems.find(adress) == mSystems.end(), "Can't store multiple systems of the same type");
			T* t = new T( std::forward<Args>(args)...);
			mSystems[adress] = t;
		}

		template<class T>
		[[nodiscard]]T* GetSystem()const {
			std::intptr_t adress = reinterpret_cast<std::intptr_t>(Internal::Adress<T>);
			auto iter = mSystems.find(adress);

			if (iter != mSystems.end())
			{
				return std::any_cast<T*>(iter->second);
			}

			return nullptr;
		}

		~GlobalRenderer() { mSystems.clear(); }

	private:
		GlobalRenderer() = default;
		static GlobalRenderer* instance;
		std::unordered_map<int64, std::any> mSystems;

	};

}