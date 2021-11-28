#pragma once
#include <type_traits>
#include <string>
#include <iostream>




#if RENDERER_DEBUG


	struct RenderAsssert {
		template <class T>
		static inline void Test(T param, const std::string& message = "") {
			static_assert(std::is_arithmetic<T>::value);
			const bool value = static_cast<bool>(param); 
			if (!param)
			{
				if (!message.empty())
				{
					std::cerr << "Render Abort\t" << message << std::endl;
				}
				abort(); 
			}
		}

	};




	
	

#elif 
#define RenderAsssert(expression) (void(0))

#endif
