#pragma once 

#include "Input/Keys.h"
#include "Window/Window.h"
#include "Core/types.h"
#include <array>


namespace Renderer::Input
{

	class InputManager;
	/*
	* @brief System that pulls events from the glfw
	*
	* This system will fetch input from the window and will forward them to the input manager if any.
	* To do it will require to have access to a global instance of the Renderer to retrieve the Manager.
	*
	*/
	class InputSystem {

	public:
		/*
		* @param InputManager to forward the events.
		* @param Window to read the events from.
		*/
		InputSystem(Observer<InputManager> manager, Observer<GLFWwindow> window);

		/*
		* @Binds new window to read the events from
		* It will unbind the previus window callback and register to the new one.
		*
		* @param new window to get the glfw callbacks from.
		*/
		void BindNewWindow(Observer<GLFWwindow> window);

		/*
		* Reads the glfw events
		*/
		void PullEvents();

		/*
		* @brief Register a new input event with key and status
		* @param key changed
		* @param is the key pressed
		*/
		void AddInputKey(KeyboardCode key, bool isUp);
	private:

		void BindCallback();
		void UnBindCallback();

	private:
		Observer<GLFWwindow> mWindow;
		Observer<InputManager> mMangaer;
		BitMask mInputMask = 0;
		BitMask mInputMaskLastFrame = 0;

	};
}