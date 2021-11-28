#pragma once 
#include "Core/types.h"
#include "Core/Handlers.h"
#include "Window/Window.h"
#include "vec2.hpp"




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

		void RegisterCallback() {}

	private:

		void INTERNAL_UpdateWindowContext();

		Window mContextWindow;

	};

}