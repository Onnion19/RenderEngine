
#include "Context/GLFWContext.h"

#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Core/Renderer.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// 
	// glfw: initialize and configure
	// ------------------------------
	Renderer::GLFW::GLFWContext context;
	// glfw window creation
	// --------------------
	auto window = context.CreateNewWindow(SCR_HEIGHT, SCR_HEIGHT, "Renderer");
	if (!window.Valid())
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	int i; 
	std::cin >> i;
	return 0;
}
