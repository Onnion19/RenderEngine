
#include "Core/Settings.h"
#include "Context/GLFWContext.h"
#include <iostream>
#include <functional>
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Utils/FrameTimer.h"
#include "scene/GameScene.h"
#include <thread>


int main()
{
	// Init GLFW context
	Renderer::GLFW::GLFWContext context;
	bool closeApp = false;
	auto window = context.CreateNewWindow(SCR_WIDTH, SCR_HEIGHT, "Renderer");
	RenderAssert(window.Valid(), "Failed to create GLFW window");
	auto closeAppToken = context.GetInputManager()->RegisterEvent([&](const auto&) { closeApp = true; }, Renderer::Input::KeyboardCode::Q, Renderer::Input::ButtonStatus::UP);

	Physics::PhysicsManager physicsManager;

	Game::GameScene scene{ physicsManager, *context.GetInputManager() };

	Timers::FrameTimer frameTimer;
	float deltaTime = 0;
	while (!closeApp)
	{
		context.PullInputEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.Update(deltaTime);
		scene.Draw();

		// update other events like input handling
		glfwSwapBuffers(window.get());
		glfwPollEvents();


		//time properties
		deltaTime = frameTimer.Tick();
		// Lock to 60 fps, don't burn the PC :D
		auto threadWait = targetFrameTime - deltaTime;
		if (threadWait > 0.f)
		{
			std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(threadWait));
			deltaTime = targetFrameTime;
		}


	}

	//Due to RAII all buffers should be cleaned.
	return 0;
}
