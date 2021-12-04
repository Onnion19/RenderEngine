#pragma once
#include <type_traits>
#include <string>
#include <iostream>







struct RenderAsssert {
	template <class T>
	static inline void Test(T param, const std::string& message = "") {
#if RENDERER_DEBUG
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
#endif
	}

};
