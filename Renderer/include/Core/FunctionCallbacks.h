#pragma once 

#include <functional>
#include "Core/AliveToken.h"

namespace Renderer::Callbacks {

	template <class ReturnType, class ... Args>
	struct Callback {
		using type = std::function<ReturnType(Args...)>;

		Callback(const std::function<ReturnType(Args...)>& f, const Renderer::Core::TokenOwner& t)
			: function(std::move(f))
			, token(t)
		{}

		std::function<ReturnType(Args...)> function;

		Renderer::Core::TokenObserver token;

		ReturnType operator()(Args&& ...  args) {
			if (token)
			{
				return function(std::forward<Args>(args)...);
			}
			return ReturnType();
		}

		explicit operator bool()const {
			return token;
		}
	};

}