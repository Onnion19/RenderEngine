#include "Input/InputManager.h"

namespace Renderer::Input {

	namespace Internal {
		using Callback = Renderer::Callbacks::Callback<void, const KeyInfo&>;
		using Token = Renderer::Core::TokenOwner;

		void UnregisterEvent(std::vector<Callback>& callbacks, const Token& t)
		{
			auto range = std::remove_if(callbacks.begin(), callbacks.end(), [&t](const Callback& callback) {return callback.token == t; });
			callbacks.erase(range, callbacks.end());
		}

		void UnregisterAllDangling(std::vector<Callback>& callbacks)
		{
			auto range = std::remove_if(callbacks.begin(), callbacks.end(), [](const Callback& callback) {return !callback.token; });
			callbacks.erase(range, callbacks.end());
		}
	}



	Renderer::Core::TokenOwner InputManager::RegisterEvent(Callback::type&& function, KeyboardCode kc, ButtonStatus bs)
	{
		Renderer::Core::TokenOwner token;
		if (bs == ButtonStatus::DOWN)
		{
			mCallbacks[kc].onDownCallbacks.emplace_back(function, token);
		}
		else if (bs == ButtonStatus::UP)
		{
			mCallbacks[kc].onUpCallbacks.emplace_back(function, token);
		}
		return token;
	}

	void InputManager::RegisterEvent(const Token& token, Callback::type&& function, KeyboardCode kc, ButtonStatus bs)
	{
		mCallbacks[kc].onDownCallbacks.emplace_back(function, token);
	}

	void InputManager::UnregisterEvent(KeyboardCode kc, ButtonStatus bs, const Token& token)
	{
		if (bs == ButtonStatus::DOWN)
		{
			Internal::UnregisterEvent(mCallbacks[kc].onDownCallbacks, token);
		}
		else if (bs == ButtonStatus::UP)
		{
			Internal::UnregisterEvent(mCallbacks[kc].onUpCallbacks, token);
		}
	}

	void InputManager::ProcessEvent(const KeyInfo& key)
	{

		auto& buffer = (key.status == ButtonStatus::DOWN) ? mCallbacks[key.code].onDownCallbacks : mCallbacks[key.code].onUpCallbacks;

		for (auto& callback : buffer)
		{
			callback(key);
		}

		Internal::UnregisterAllDangling(buffer);
	}
}