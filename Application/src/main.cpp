
#include "Context/GLFWContext.h"

#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool close = false;

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	auto lambda = [](Renderer::Input::KeyInfo key) {
		std::cout << static_cast<int32>(key.code) << std::endl;
	};

	auto token = context.GetInputManager()->RegisterEvent(lambda, Renderer::Input::KeyboardCode::A, Renderer::Input::ButtonStatus::DOWN);

	while (!close)
	{
		context.PullInputEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;
		glfwPollEvents();
		glfwSwapBuffers(window.get());
	}
	return 0;
}
