#pragma once 
#include "glad/glad.h"
#include "Core/types.h"
#include "Core/Handlers.h"
#include "Window/Window.h"
#include "vec2.hpp"
#include <memory>

namespace  Renderer::Input {
	class InputManager;
	class InputSystem;
}


namespace Renderer::GLFW
{

	class GLFWContext {
	public:

		using Window = Renderer::Window::GLFWwindowPointer;
		using WindowObserver = Renderer::Core::ObserverHandler<GLFWwindow>;
		/*
			Initializes all GLFW context and allows start operation with it.
		*/
		GLFWContext();
		~GLFWContext();

		/*
			Creates a new glfw Window, asigns as a current Context and returns an observer to it.
		*/
		WindowObserver CreateNewWindow(int16 Widht, int16 Height, string name);

		/*
			Takes ownership of the Window provided and sets it as the current context.
		*/
		WindowObserver UseCustomWindow(Window& window);


		[[nodiscard]] glm::ivec2 GetWindowSize()const;
		[[nodiscard]] glm::ivec2 GetWindowPos()const;

		/*
			Process all the input events and clears the buffer.
		*/
		void PullInputEvents();

		Renderer::Input::InputManager* GetInputManager()const;

	private:

		void INTERNAL_UpdateWindowContext();

		Window mContextWindow;
		std::unique_ptr<Renderer::Input::InputManager> mInputManager;

		//Cached pointers just for avoid some extra look up;
		Observer<Renderer::Input::InputSystem> mInputSystem;

	};

}