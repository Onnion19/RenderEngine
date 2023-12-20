
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool close = false;

int main()
{

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
	auto lambda = [](Renderer::Input::KeyInfo key) {

		string status = (key.status == Renderer::Input::ButtonStatus::DOWN) ? "DOWN" : "UP";

		std::cout << status << " Key: " << Renderer::Input::DebugKeyCodeText(key.code) << " Modifier: " << Renderer::Input::DebugKeyCodeText(key.modifier) << std::endl << std::endl;
		};

	auto token = context.GetInputManager()->RegisterEvent(lambda, Renderer::Input::KeyboardCode::None, Renderer::Input::ButtonStatus::DOWN);
	context.GetInputManager()->RegisterEvent(token, lambda, Renderer::Input::KeyboardCode::None, Renderer::Input::ButtonStatus::UP);



	//Create Mesh class 
		// Contains all data: 
		// Positions , color, etc... 
		// Metaprogramming to figure out which buffers requires
		// Assimp? 
		// Dynamic vs Static meshes
		// Animations? 
	struct Vertice2D { float x, y; };
	std::vector<Vertice2D> points = {
		{-0.5f , -0.5f},
		{0.5f,-0.5f},
		{0.0f,0.5f}
	};





	//Vertex buffer object
	Renderer::GL::OpenGlBuffer<Vertice2D> vbo(OpenGLUtils::Buffer::BufferType::ARRAY);
	vbo.Insert(points);
	vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);


	Renderer::GL::VertexAtributeObject vao;
	vao.Bind();
	Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Vertice2D> properties{ 0 ,3, OpenGLUtils::Buffer::GLType::FLOAT, false };
	vao.EnableAndDefineAttributePointer(properties);
	//Vertex attribute object
	//GLuint vao = 0;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	// Create material
	  // Add shader data to the material
	  // Shader library with shared pointer
	  // Free shader free
	  // Shader class 
	  // FileSystem

	//Batching?
	const char* vertex_shader =
		"#version 400\n"
		"in vec2 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";


	//Render queue

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);

	while (!close)
	{
		//this is wrong, this will only work for one window. See https://discourse.glfw.org/t/how-to-create-multiple-window/1398/2
		context.PullInputEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling

		glfwSwapBuffers(window.get());
	}
	return 0;
}
