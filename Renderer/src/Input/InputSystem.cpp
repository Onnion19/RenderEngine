#include "Input/InputSystem.h"
#include "GLFW/glfw3.h"
#include "Input/InputManager.h"
#include "Core/RenderAssert.h"
#include "Core/Renderer.h"



namespace Renderer::Input {

	namespace Internal {
		KeyboardCode GlfwToKeyCode(int glfwKeyCode)
		{
			switch (glfwKeyCode) {
			case GLFW_KEY_RIGHT_SHIFT: [[fallthrough]];
			case GLFW_KEY_LEFT_SHIFT:
				return KeyboardCode::Shift;
				break;
			case GLFW_KEY_RIGHT_CONTROL: [[fallthrough]];
			case GLFW_KEY_LEFT_CONTROL:
				return KeyboardCode::Cntrl;
				break;
			case GLFW_KEY_RIGHT_ALT: [[fallthrough]];
			case GLFW_KEY_LEFT_ALT:
				return KeyboardCode::Alt;
				break;

			default:
				const int key = (glfwKeyCode - 'A');
				const int MaxKey = 'Z' - 'A';
				const int MinKey = 0;
				if (key >= MinKey && key <= MaxKey)
				{
					return static_cast<KeyboardCode>(Bit_(key + 1));
				}
				break;
			}

			return KeyboardCode::None;
		}


		BitMask GetModifierMosk(BitMask input)
		{
			auto mask =  BuildBitMaskFromKeyboardCode(KeyboardCode::Alt, KeyboardCode::Cntrl, KeyboardCode::Shift);
			return input & mask;
		}

		KeyboardCode GetModifierCode(BitMask mask)
		{
			if (mask & BuildBitMaskFromKeyboardCode(KeyboardCode::Alt))
			{
				return KeyboardCode::Alt;
			}
			else if (mask & BuildBitMaskFromKeyboardCode(KeyboardCode::Cntrl))
			{
				return KeyboardCode::Cntrl;
			}
			else if (mask & BuildBitMaskFromKeyboardCode(KeyboardCode::Shift))
			{
				return KeyboardCode::Shift;
			}

			return KeyboardCode::None;
		}

	}


	void InputSystem::AddInputKey(KeyboardCode code, bool isUp) {

		if (isUp)
		{
			mInputMask &= ~static_cast<BitMask>(code);
		}
		else
		{
			mInputMask |= static_cast<BitMask>(code);
		}

	}

	InputSystem::InputSystem(Observer<InputManager> manager, Observer<GLFWwindow> window)
	{
		RenderAssert(manager != nullptr, "No Input manager detected");
		mMangaer = manager;
		mWindow = window;
		BindCallback();

	}

	void InputSystem::BindNewWindow(Observer<GLFWwindow> window)
	{
		UnBindCallback();
		mWindow = window;
		BindCallback();
	}

	void InputSystem::BindCallback() {

		if (!mWindow.Valid())return;

		glfwSetKeyCallback(mWindow.get(), []([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]]int scancode, int action, [[maybe_unused]] int mods) {
			InputSystem* system = GlobalRenderer::GetSystem<InputSystem>();
			RenderAssert(system != nullptr, "No Input System detected");

			auto k = Internal::GlfwToKeyCode(key);
			system->AddInputKey(k, action == GLFW_RELEASE);
		});

	}

	void InputSystem::UnBindCallback()
	{
		if (!mWindow.Valid())return;
		glfwSetKeyCallback(mWindow.get(), NULL);
	}

	void InputSystem::PullEvents()
	{
		if (mInputMask == mInputMaskLastFrame) return; // no input event

		KeyboardCode modifierKey = Internal::GetModifierCode(mInputMask);
		KeyboardCode lastModifierKey = Internal::GetModifierCode(mInputMaskLastFrame);

		//todo: optimize
		for (int i = 1; i < 27; i++) //Ignore control values, see Keys.h
		{
			//Input for this bit has changed
			const bool isPressed = AreBitsSets(mInputMask, i);
			const bool wasPressed = AreBitsSets(mInputMaskLastFrame, i);

			if ((modifierKey != lastModifierKey) && isPressed)//Remove the key since the modifier is no longer valid
			{
				const ButtonStatus status = ButtonStatus::UP;
				const KeyboardCode keyCode = GetKeyFromLiteral(Bit_(i));
				const KeyInfo key = { status, keyCode, lastModifierKey };
				mMangaer.get()->ProcessEvent(key);
				//Force release
				AddInputKey(keyCode, true);
			}
			else if (isPressed != wasPressed)
			{
				const ButtonStatus status = (isPressed) ? ButtonStatus::DOWN : ButtonStatus::UP;
				const KeyInfo key = { status, GetKeyFromLiteral(Bit_(i)), modifierKey };
				mMangaer.get()->ProcessEvent(key);
			}
		}

		mInputMaskLastFrame = mInputMask;
	
	}
}