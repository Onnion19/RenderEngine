
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Camera.h"
#include "OpenGl/QuadBatcher.h"
#include "OpenGl/Program.h"
#include "OpenGl/VertexAttributeObject.h"
#include "Type/Transform.h"
#include "Type/Color.h"
#include "Physics/PhysicsManager.h"
#include "scene/BlocksBuilder.h"
#include "Utils/FrameTimer.h"
#include "GameObject/Ball.h"
#include <thread>


// settings
constexpr unsigned int SCR_WIDTH = 1920;
constexpr unsigned int SCR_HEIGHT = 1080;

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

		manager.RegisterEvent(aliveToken, [&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(0.f, cameraMovement, 0.f));
			}, Renderer::Input::KeyboardCode::A, Renderer::Input::ButtonStatus::DOWN);

		manager.RegisterEvent(aliveToken, [&](Renderer::Input::KeyInfo) {
			camera.Translate(vec3(0.f, -cameraMovement, 0.f));
			}, Renderer::Input::KeyboardCode::D, Renderer::Input::ButtonStatus::DOWN);
	}

private:
	Renderer::Core::TokenOwner aliveToken;
};


Renderer::GL::OrthoCamera GenerateCamera()
{
	Renderer::GL::OrthoCamera camera{ SCR_WIDTH,SCR_HEIGHT,0.1f,100.f };
	camera.Translate(vec3{ 0.f,0.f,-10.f });
	return camera;
}

Renderer::GL::Program CreateDefaultProgram(const auto& camera)
{
	// Takes in the camera cause the projection is always constant
	std::filesystem::path vertex{ "Assets/Shaders/DefaultShader.vert" };
	std::filesystem::path fragment{ "Assets/Shaders/DefaultShader.frag" };
	Renderer::GL::Shader vs(vertex, OpenGLUtils::Shader::Type::VERTEX);
	Renderer::GL::Shader fs(fragment, OpenGLUtils::Shader::Type::FRAGMENT);
	Renderer::GL::Program program{ vs, fs };
	program.SetUniformMatrix4("model", glm::identity<mat4>());
	program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

	return program;
}


constexpr float targetFrameTime = 16.666f;//60fps

int main()
{
	Renderer::GLFW::GLFWContext context;
	auto window = context.CreateNewWindow(SCR_WIDTH, SCR_HEIGHT, "Renderer");
	RenderAssert(window.Valid(), "Failed to create GLFW window");

	bool closeApp = false;
	auto closeAppToken = context.GetInputManager()->RegisterEvent([&](const auto&) { closeApp = true; }, Renderer::Input::KeyboardCode::Q, Renderer::Input::ButtonStatus::UP);

	Physics::PhysicsManager physicsManager;

	auto camera = GenerateCamera();
	CameraMovement movement{ camera, *context.GetInputManager() };


	auto blocks = Game::BlockBuilder::BuildBlocks(physicsManager, "Assets/level.blocks", vec3{ 870.f, 50, 0.f }, vec3{ 90.f, SCR_HEIGHT * 0.9f, -1.f }, vec3{ 10.f, 10.f, 0.f });

	if (!blocks)
	{
		std::cout << blocks.error() << std::endl;
		return -1;
	}

	auto defaultProgram = CreateDefaultProgram(camera);
	Renderer::GL::QuadBatcher <Renderer::Geometry::Point2D, Renderer::Type::RawColor > batch{ defaultProgram };
	for (auto& block : blocks.value())
	{
		auto id = batch.AddQuad(block.getVBOData());
		block.RegisterOnCollideCallback([&batch, id](const vec3&) {batch.HideQuad(id); });
	}
	batch.SendQuadDataToGPU();
	//Ball(Physics::PhysicsManager& manager, const Renderer::GL::Program& shaderProgram, const vec3& position, float radius, float speed, const vec3& initialDirection = glm::normalize(vec3{ 0.1f, -0.9f,0.f }));
	Game::Ball ball(physicsManager, CreateDefaultProgram(camera), vec3{500.f,500.f, -1.f}, 50.f, 40.f, glm::normalize(vec3{ 0.1f, +0.9f,0.f }));

	Timers::FrameTimer frameTimer;
	float deltaTime = 0;
	while (!closeApp)
	{
		//this is wrong, this will only work for one window. See https://discourse.glfw.org/t/how-to-create-multiple-window/1398/2
		context.PullInputEvents();

		// Update
		// Pad.Update();
		ball.Update(deltaTime);
		// physics update
		// Check Ball Collisions;
		// Check Game Over;
		// Draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Pad.Draw();
		batch.Draw(camera);
		ball.Draw(camera);

		// update other events like input handling
		glfwSwapBuffers(window.get());
		glfwPollEvents();


		// time properties
		deltaTime = frameTimer.Tick();
		// Lock to 60 fps, don't burn the PC :D
		auto threadWait = targetFrameTime - deltaTime;
		if (threadWait > 0.f)
		{
			std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(threadWait));
			deltaTime = targetFrameTime;
		}

	}
	return 0;
}
