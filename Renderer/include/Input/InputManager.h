#pragma once 

#include "Input/Keys.h"
#include "Core/FunctionCallbacks.h"
#include <map>
#include <vector>


namespace Renderer::Input {

	/*
	* @brief handles input events and forwards to the consumers
	* 
	* This is the user facing interface when registering to any input event.
	* Basically it stores functions callbacks with a token to check if the binded object is still alive.
	*/
	class InputManager {

		struct KeyCallback {
			using Callback = Renderer::Callbacks::Callback<void, const KeyInfo&>;

			std::vector<Callback> onUpCallbacks;
			std::vector< Callback> onDownCallbacks;
		};

		using Callback = Renderer::Callbacks::Callback<void, KeyInfo>;
		using KeyCallbackMap = std::map<BitMask, KeyCallback>;
		using Token = Renderer::Core::TokenOwner;
#if RENDERER_DEBUG
	private:
		Token debugInputToken;
	public:
		InputManager();
#else
	public:
		InputManager() = default;
#endif

		[[nodiscard]] Token RegisterEvent(Callback::type&& function, KeyboardCode code, ButtonStatus stauts);
		[[nodiscard]] Token RegisterEvent(Callback::type&& function, BitMask code, ButtonStatus stauts);
		void RegisterEvent(const Token&, Callback::type&& function, KeyboardCode code, ButtonStatus status);
		void RegisterEvent(const Token&, Callback::type&& function, BitMask code, ButtonStatus status);
		void UnregisterEvent(KeyboardCode code, ButtonStatus status, const Token& token);
		void UnregisterEvent(BitMask code, ButtonStatus status, const Token& token);

	private:
		void ProcessEvent(const KeyInfo& key);

	private:
		KeyCallbackMap mCallbacks;
		friend class InputSystem;
	};

}