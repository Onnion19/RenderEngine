#include "Input/InputSystem.h"
#include "GLFW/glfw3.h"
#include "Input/InputManager.h"
#include "Core/RenderAssert.h"



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

		

	}

	InputSystem::InputSystem(InputManager* manager, Renderer::Window::GLFWwindowPointer window)
	{
		RenderAsssert::Test(manager != nullptr, "No Input manager detected");
		RenderAsssert::Test(window != nullptr, "No Window detected");
		mMangaer = manager;

		glfwSetKeyCallback(window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {});

	}

	BitMask InputSystem::PullEvents()
	{
		return {};
	}
}