
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Camera.h"
#include "OpenGl/QuadBatcher.h"
#include "OpenGl/Quad.h"
#include "OpenGl/Program.h"
#include "OpenGl/VertexAttributeObject.h"
#include "Type/Transform.h"
#include "Type/Color.h"

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 o_color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
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
	Renderer::GL::OrthoCamera camera{ 500.f,500.f,0.1f,100.f };
	camera.Translate(vec3{ 0.f,0.f,-10.f});

	constexpr auto cameraMovement = 10.f;
	auto t1 = context.GetInputManager()->RegisterEvent([&](Renderer::Input::KeyInfo) {
		camera.Translate(vec3(cameraMovement, 0.f, 0.f));
		}, Renderer::Input::KeyboardCode::W, Renderer::Input::ButtonStatus::DOWN);

	auto t2 = context.GetInputManager()->RegisterEvent([&](Renderer::Input::KeyInfo) {
		camera.Translate(vec3(-cameraMovement, 0.f, 0.f));
		}, Renderer::Input::KeyboardCode::S, Renderer::Input::ButtonStatus::DOWN);

	auto t3 = context.GetInputManager()->RegisterEvent([&](Renderer::Input::KeyInfo) {
		camera.Translate(vec3(0.f, cameraMovement, 0.f));
		}, Renderer::Input::KeyboardCode::A, Renderer::Input::ButtonStatus::DOWN);

	auto t4 = context.GetInputManager()->RegisterEvent([&](Renderer::Input::KeyInfo) {
		camera.Translate(vec3(0.f, -cameraMovement, 0.f));
		}, Renderer::Input::KeyboardCode::D, Renderer::Input::ButtonStatus::DOWN);



	Renderer::GL::BasicQuad quad{ Core::Transform{ vec3{0.f}, vec3{}, vec3{30.f} }, Renderer::Type::BLUE };
	Renderer::GL::BasicQuad quad2{ Core::Transform{ vec3{20.f,20.f, -1.f}, vec3{}, vec3{30.f} } };

	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch;
	batch.AddQuad(quad.GetVBOData());
	batch.AddQuad(quad2.GetVBOData());
	batch.SendQuadDataToGPU();
	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch2;
	batch2.SendQuadDataToGPU();

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
		program.SetUniformMatrix4("model", glm::identity<mat4>());
		auto [view, projection] = camera.GetCameraAndProjectionMatrices();
		program.SetUniformMatrix4("view", view);
		program.SetUniformMatrix4("projection", projection);

		std::cout << "\n\nView Matrix\n";
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << view[i][j] << "\t";
			}
			std::cout << std::endl;
		}

		batch2.Draw();
		batch.Draw();
		// update other events like input handling

		glfwSwapBuffers(window.get());
	}
	return 0;
}
