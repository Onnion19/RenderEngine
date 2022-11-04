#pragma once 

#include "GLFW/glfw3.h"
#include <iostream>
#include "Core/RenderAssert.h"

namespace Renderer::Window {

	struct GLFWwindowDeleter {
		void operator() (GLFWwindow* ptr) {

			RenderAssert(ptr != nullptr, "Attempting to delete a null window");
			glfwDestroyWindow(ptr);
		}
	};

	using GLFWwindowPointer = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

}