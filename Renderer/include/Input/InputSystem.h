#pragma once 

#include "Input/Keys.h"
#include "Window/Window.h"


namespace Renderer::Input
{

	class InputManager;

	class InputSystem {

	public:
		InputSystem(InputManager* manager, Renderer::Window::GLFWwindowPointer window);

		BitMask PullEvents();
	private:


	private:
		Renderer::Window::GLFWwindowPointer mWindow;
		InputManager* mMangaer;
		BitMask mInputMask;
	};
}