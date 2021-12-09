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
		return RegisterEvent(std::move(function), static_cast<BitMask>(kc), bs);
	}

	Renderer::Core::TokenOwner InputManager::RegisterEvent(Callback::type&& function, BitMask mask, ButtonStatus bs)
	{
		Renderer::Core::TokenOwner token;
		if (bs == ButtonStatus::DOWN)
		{
			mCallbacks[mask].onDownCallbacks.emplace_back(function, token);
		}
		else if (bs == ButtonStatus::UP)
		{
			mCallbacks[mask].onUpCallbacks.emplace_back(function, token);
		}
		return token;
	}

	void InputManager::RegisterEvent(const Token& token, Callback::type&& function, KeyboardCode kc, ButtonStatus bs)
	{
		RegisterEvent(token, std::move(function), static_cast<BitMask>(kc), bs);
	}

	void InputManager::RegisterEvent(const Token& token, Callback::type&& function, BitMask mask, ButtonStatus bs)
	{
		if (bs == ButtonStatus::DOWN)
		{
			mCallbacks[mask].onDownCallbacks.emplace_back(function, token);
		}
		else
		{
			mCallbacks[mask].onUpCallbacks.emplace_back(function, token);
		}
	}

	void InputManager::UnregisterEvent(KeyboardCode kc, ButtonStatus bs, const Token& token)
	{
		UnregisterEvent(static_cast<BitMask>(kc), bs, token);
	}

	void InputManager::UnregisterEvent(BitMask mask, ButtonStatus bs, const Token& token)
	{
		if (bs == ButtonStatus::DOWN)
		{
			Internal::UnregisterEvent(mCallbacks[mask].onDownCallbacks, token);
		}
		else if (bs == ButtonStatus::UP)
		{
			Internal::UnregisterEvent(mCallbacks[mask].onUpCallbacks, token);
		}
	}


	void InputManager::ProcessEvent(const KeyInfo& key)
	{
		BitMask mask = static_cast<BitMask>(key.code);
		if (key.modifier != KeyboardCode::None) {
			mask |= static_cast<BitMask>(key.modifier);
		}

		{
			auto& buffer = (key.status == ButtonStatus::DOWN) ? mCallbacks[mask].onDownCallbacks : mCallbacks[mask].onUpCallbacks;

			for (auto& callback : buffer)
			{
				callback(key);
			}

			Internal::UnregisterAllDangling(buffer);
		}

		//Call for any key: 
		{
			auto AnyKeyMask = static_cast<BitMask>(KeyboardCode::None);
			auto& buffer = (key.status == ButtonStatus::DOWN) ? mCallbacks[AnyKeyMask].onDownCallbacks : mCallbacks[AnyKeyMask].onUpCallbacks;

			for (auto& callback : buffer)
			{
				callback(key);
			}

			Internal::UnregisterAllDangling(buffer);
		}


	}


}