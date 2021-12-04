#pragma once 

#include "GLFW/glfw3.h"
#include <iostream>

namespace Renderer {
	namespace Window {
		struct GLFWwindowDeleter {
			void operator() (GLFWwindow* ptr){
				if (ptr != nullptr) {
					glfwDestroyWindow(ptr);
				}
				
#if RENDERER_DEBUG
				if (!ptr) {
					std::cerr << "GLFWwindowDeleter trying to delete a null pointer" << std::endl;
					throw("");
				}
#endif 
			}
		};

		using GLFWwindowPointer = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;		
		
	}

}