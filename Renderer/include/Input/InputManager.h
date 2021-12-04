#pragma once 

#include "Input/Keys.h"
#include "Core/FunctionCallbacks.h"
#include <map>
#include <vector>


namespace Renderer::Input {

	class InputManager {

		struct KeyCallback {
			using Callback = Renderer::Callbacks::Callback<void, const KeyInfo&>;

			std::vector<Callback> onUpCallbacks;
			std::vector< Callback> onDownCallbacks;
		};

		using Callback = Renderer::Callbacks::Callback<void, KeyInfo>;
		using KeyCallbackMap = std::map<KeyboardCode, KeyCallback>;
		using Token = Renderer::Core::TokenOwner;
	public:
		InputManager() = default;

		Token RegisterEvent(Callback::type&& function, KeyboardCode code, ButtonStatus stauts);
		void RegisterEvent(const Token&, Callback::type&& function, KeyboardCode code, ButtonStatus status);
		void UnregisterEvent(KeyboardCode code, ButtonStatus status, const Token& token);

	private: 
		void ProcessEvent(const KeyInfo& key);

	private:
		KeyCallbackMap mCallbacks;

		friend class InputSystem;
	};

}