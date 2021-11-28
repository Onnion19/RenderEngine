#include <glad/glad.h>
#include "Context/GLFWContext.h"

#include <iostream>
#include <functional>
#include "Window/Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

	// 
	// glfw: initialize and configure
	// ------------------------------
	Renderer::GLFW::GLFWContext context;

	{
		Renderer::Window::GLFWwindowPointer p;
	}

	// glfw window creation
	// --------------------
	auto window = context.CreateNewWindow(SCR_HEIGHT, SCR_HEIGHT, "Renderer");
	if (!window.Valid())
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window.get(), [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); });

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.get()))
	{
		// input
		// -----
		processInput(window.get());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}