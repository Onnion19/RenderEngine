
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/QuadBatcher.h"
#include "OpenGl/Program.h"
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

		std::string status = (key.status == Renderer::Input::ButtonStatus::DOWN) ? "DOWN" : "UP";

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




	//std::vector<std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>> points = {
	//{{-0.f ,0.5f}, Renderer::Type::RED},
	//{{0.5, 0.5f}, Renderer::Type::RED },
	//{{0.5f, -0.f}, Renderer::Type::GREEN},
	//{{-0.f, -0.f}, Renderer::Type::BLUE} };

	//std::vector<std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>> points2 = {
	//	{{-0.5f, 0.f}, Renderer::Type::RED},
	//	{{0.f, 0.f}, Renderer::Type::RED},
	//	{{0.f, -0.3f}, Renderer::Type::RED},
	//	{{-0.5f, -0.3f}, Renderer::Type::BLUE} };


	Renderer::GL::BasicQuad quad{ Core::Transform{ vec3{}, vec3{}, vec3{0.25f} } };
	Renderer::GL::BasicQuad quad2{ Core::Transform{ vec3{-0.25}, vec3{}, vec3{0.25f} } , Renderer::Type::BLUE };

	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch;
	batch.AddQuad(quad.GetVBOData());
	batch.AddQuad(quad2.GetVBOData());
	batch.SendQuadDataToGPU();

	Renderer::GL::Shader vs(std::string_view(vertexShaderSource), OpenGLUtils::Shader::Type::VERTEX);
	Renderer::GL::Shader fs(std::string_view(fragmentShaderSource), OpenGLUtils::Shader::Type::FRAGMENT);
	Renderer::GL::Program program{ vs, fs };
	program.LinkProgram();
	program();

	auto lambda2 = [&](Renderer::Input::KeyInfo /*key*/) {
		static bool a = true;
		if (a)
			batch.HideQuad(0);
		else
			batch.ShowQuad(0);
		a = !a;
		};

	auto token2 = context.GetInputManager()->RegisterEvent(lambda2, Renderer::Input::KeyboardCode::F, Renderer::Input::ButtonStatus::UP);

	while (!close)
	{
		//this is wrong, this will only work for one window. See https://discourse.glfw.org/t/how-to-create-multiple-window/1398/2
		context.PullInputEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			close = true;
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		batch.Draw();
		// update other events like input handling

		glfwSwapBuffers(window.get());
	}
	return 0;
}
