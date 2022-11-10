#pragma once
#include <type_traits>
#include <string>
#include <iostream>


struct RenderAsssert {
#if RENDERER_DEBUG
	template <class T>
	static inline void Test(T param, const std::string& message = "") {
		static_assert(std::is_arithmetic<T>::value);
		if (!param)
		{
			if (!message.empty())
			{
				std::cerr << "Render Abort\t" << message << std::endl;
			}
			abort();
		}
	}
#else 
	template <class T>
	static inline void Test([[maybe_unused]] T param, [[maybe_unused]]const std::string& message = "") {

	}
#endif

};
