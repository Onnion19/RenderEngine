#pragma once 

#include "Core/types.h"
#include <unordered_map>
#include <any>
#include "Core/RenderAssert.h"
#include <optional>

namespace Renderer
{

	namespace Internal {
		template<class T>
		void Adress() {}

		template<class T>
		constexpr std::intptr_t GetHash()
		{
			return reinterpret_cast<std::intptr_t>(Adress<T>);
		}
	}



	/*
		I HATE TO DO THIS KIND OF GLOBAL STUFF ONLY DUE TO
		GLFW IS BASED IN FREE FUNCTIONS AND CAN'T BIND OBJECT MEMBER FUNCS.
	*/

	/*
	* @brief Global class storing the engine systems
	* This is meant to only have a global acces to the registered systems.
	* Any class can be a system 
	*/
	class GlobalRenderer {

	public:

		template<class T, class ... Args>
		static Observer<T> CreateSystem(Args&& ... args) {
			const std::intptr_t adress = Internal::GetHash<T>();
			RenderAsssert::Test(mSystems.find(adress) == mSystems.end(), "Can't store multiple systems of the same type");
			T* t = new T(std::forward<Args>(args)...);
			mSystems[adress] = t;
			return Core::MakeObserver(t);
		}

		template<class T>
		[[nodiscard]] static T* GetSystem() {
			std::intptr_t adress = reinterpret_cast<std::intptr_t>(Internal::Adress<T>);
			auto iter = mSystems.find(adress);

			if (iter != mSystems.end())
			{
				return std::any_cast<T*>(iter->second);
			}

			return nullptr;
		}


		//Remember to trigger this at the end of the app to avoid memory leak
		static void Reset() {

			for (auto system : mSystems)
			{
				auto s = std::any_cast<void*>(system);
				delete s;
			}

			mSystems.clear();

		}

	private:
		GlobalRenderer() = delete;
		static std::unordered_map<int64, std::any> mSystems;

	};

}