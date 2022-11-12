#include "Context/GLFWContext.h"
#include "GLFW/glfw3.h"
#include "Core/RenderAssert.h"
#include "Input/InputManager.h"
#include "Input/InputSystem.h"
#include "Core/Renderer.h"

namespace Renderer::GLFW {

	GLFWContext::GLFWContext()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mInputManager.reset(new Renderer::Input::InputManager());
		mInputSystem = Renderer::GlobalRenderer::CreateSystem<Renderer::Input::InputSystem>(mInputManager.get(), nullptr);
		RenderAssert(mInputSystem.Valid(), "Issue when creating Input System");
	}

	GLFWContext::~GLFWContext()
	{
		glfwTerminate();
	}

	GLFWContext::WindowObserver GLFWContext::CreateNewWindow(int16 Widht, int16 Height, string name)
	{
		mContextWindow = Window(glfwCreateWindow(Widht, Height, name.c_str(), nullptr, {}));
		INTERNAL_UpdateWindowContext();
		INTERNAL_LoadGlad();
		mInputSystem.get()->BindNewWindow(mContextWindow.get());
		return Renderer::Core::MakeObserver(mContextWindow.get());
	}

	GLFWContext::WindowObserver GLFWContext::UseCustomWindow(Window& window)
	{
		mContextWindow = std::move(window);
		INTERNAL_UpdateWindowContext();
		mInputSystem.get()->BindNewWindow(mContextWindow.get());
		return  Renderer::Core::MakeObserver(mContextWindow.get());
	}



	void GLFWContext::INTERNAL_UpdateWindowContext()
	{
		RenderAssert(mContextWindow.get() != nullptr, "Context has now window associated");
		glfwMakeContextCurrent(mContextWindow.get());
	}

	void GLFWContext::INTERNAL_LoadGlad() {
		[[maybe_unused]] const auto loaded =  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RenderAssert(loaded, "Failed To initialize glad");
	}


	glm::ivec2 GLFWContext::GetWindowSize()const
	{
		glm::ivec2 vec = {};
		if (mContextWindow)
		{
			glfwGetWindowSize(mContextWindow.get(), &vec.x, &vec.y);
		}
		return vec;
	}


	glm::ivec2 GLFWContext::GetWindowPos()const
	{
		glm::ivec2 vec = {};
		if (mContextWindow)
		{
			glfwGetWindowPos(mContextWindow.get(), &vec.x, &vec.y);
		}
		return vec;
	}

	void GLFWContext::PullInputEvents() {
		mInputSystem.get()->PullEvents();
	}

	Renderer::Input::InputManager* GLFWContext::GetInputManager()const
	{
		return mInputManager.get();
	}
}