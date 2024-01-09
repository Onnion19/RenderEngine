
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
constexpr unsigned int SCR_WIDTH = 1920;
constexpr unsigned int SCR_HEIGHT = 1080;

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



struct CameraMovement {

	CameraMovement(auto& camera, Renderer::Input::InputManager& manager)
	{
		constexpr auto cameraMovement = 10.f;
		aliveToken = manager.RegisterEvent([&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(cameraMovement, 0.f, 0.f));
			}, Renderer::Input::KeyboardCode::W, Renderer::Input::ButtonStatus::DOWN);

		manager.RegisterEvent(aliveToken, [&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(-cameraMovement, 0.f, 0.f));
			}, Renderer::Input::KeyboardCode::S, Renderer::Input::ButtonStatus::DOWN);

		manager.RegisterEvent(aliveToken,[&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(0.f, cameraMovement, 0.f));
			}, Renderer::Input::KeyboardCode::A, Renderer::Input::ButtonStatus::DOWN);

		manager.RegisterEvent(aliveToken, [&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(0.f, -cameraMovement, 0.f));
			}, Renderer::Input::KeyboardCode::D, Renderer::Input::ButtonStatus::DOWN);
	}

private: 
	Renderer::Core::TokenOwner aliveToken;
};


Renderer::GL::Program CreateDefaultProgram(const auto& camera)
{

	Renderer::GL::Shader vs(std::string_view(vertexShaderSource), OpenGLUtils::Shader::Type::VERTEX);
	Renderer::GL::Shader fs(std::string_view(fragmentShaderSource), OpenGLUtils::Shader::Type::FRAGMENT);
	Renderer::GL::Program program{ vs, fs };
	program.SetUniformMatrix4("model", glm::identity<mat4>());
	program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

	return program;
}

bool close = false;
int main()
{

	// glfw: initialize and configure
	// ------------------------------
	Renderer::GLFW::GLFWContext context;
	// glfw window creation
	// --------------------
	auto window = context.CreateNewWindow(SCR_WIDTH, SCR_HEIGHT, "Renderer");
	RenderAssert(window.Valid(), "Failed to create GLFW window");


	
	Renderer::GL::OrthoCamera camera{ SCR_WIDTH,SCR_HEIGHT,0.1f,100.f };
	camera.Translate(vec3{ 0.f,0.f,-10.f });

	CameraMovement movement{camera, *context.GetInputManager()};
	auto defaultProgram = CreateDefaultProgram(camera);

	Renderer::GL::BasicQuad quad{ Core::Transform{ vec3{0.f}, vec3{}, vec3{30.f} }, Renderer::Type::BLUE };
	Renderer::GL::BasicQuad quad2{ Core::Transform{ vec3{20.f,20.f, -1.f}, vec3{}, vec3{30.f} } };



	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch{ defaultProgram };
	batch.AddQuad(quad.GetVBOData());
	batch.AddQuad(quad2.GetVBOData());
	batch.SendQuadDataToGPU();
	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch2{ defaultProgram };
	batch2.SendQuadDataToGPU();



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
		batch2.Draw(camera);
		batch.Draw(camera);
		// update other events like input handling

		glfwSwapBuffers(window.get());
	}
	return 0;
}
