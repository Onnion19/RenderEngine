
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/QuadBatcher.h"
#include "OpenGl/Quad.h"
#include "Type/Transform.h"
#include "Type/Color.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 o_color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   o_color = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 o_color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(o_color, 1.0f);\n"
"}\n\0";


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




	std::vector<std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>> points = {
	{{-0.f ,0.5f}, Renderer::Type::RED},
	{{0.5, 0.5f}, Renderer::Type::RED },
	{{0.5f, -0.f}, Renderer::Type::GREEN},
	{{-0.f, -0.f}, Renderer::Type::BLUE} };

	std::vector<std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>> points2 = {
		{{-0.5f, 0.f}, Renderer::Type::RED},
		{{0.f, 0.f}, Renderer::Type::RED},
		{{0.f, -0.3f}, Renderer::Type::RED},
		{{-0.5f, -0.3f}, Renderer::Type::BLUE} };

	//std::vector<Renderer::Geometry::Point2D>points = {
	//{0.5, 0.5f},
	//{-0.f ,0.5f},
	//{0.5f, -0.f} };

	//std::vector<std::tuple<Renderer::Geometry::Point2D>>points2 = {
	//{{-0.5f, 0.f}},
	//{{0.f, 0.f}},
	//{{0.f, -0.3f}},
	//{{-0.5f, -0.3f}} };

	//////Vertex buffer object
	//Renderer::GL::OpenGlBuffer<Renderer::Geometry::Point2D> vbo(OpenGLUtils::Buffer::BufferType::ARRAY);
	//vbo.Insert(points);
	//vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);

	//Renderer::GL::VertexAtributeObject vao;
	//vao.Bind();
	//Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Renderer::Geometry::Point2D> properties{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
	//vao.EnableAndDefineAttributePointer(properties);

	//float vertices[] = {
	//	0.5f,  0.5f, 0.0f, 1.f, 0.f, 0.f, // top right + color
	//	0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f, // bottom right
	//   -0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f, // bottom left
	//   -0.5f,  0.5f, 0.0f, 1.f, 0.f, 1.f // top left 
	//};
	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 3,  // first Triangle
	//	1, 2, 3   // second Triangle
	//};
	//unsigned int VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	//// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);
	

	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch;
	batch.AddQuad(points);
	batch.AddQuad(points2);
	batch.SendQuadDataToGPU();


	//Core::Transform2D transform{ {0.5f,0.5f} , {0.2f, 0.2f}, 0.f };
	//Renderer::GL::BasicQuad quad(transform);



	// Create material
	  // Add shader data to the material
	  // Shader library with shared pointer
	  // Free shader free
	  // Shader class 
	  // FileSystem

	//Render queue
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderSource, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderSource, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);

	//auto lambda2 = [&](Renderer::Input::KeyInfo /*key*/) {
	//	batch.RemoveQuad(0);
	//	};

	//auto token2 = context.GetInputManager()->RegisterEvent(lambda2, Renderer::Input::KeyboardCode::F, Renderer::Input::ButtonStatus::UP);

	while (!close)
	{
		//this is wrong, this will only work for one window. See https://discourse.glfw.org/t/how-to-create-multiple-window/1398/2
		context.PullInputEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw points 0-3 from the currently bound VAO with current in-use shader
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		batch.Draw();
		//quad.Draw();
		// update other events like input handling

		glfwSwapBuffers(window.get());
	}
	return 0;
}
