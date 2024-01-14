#pragma once

#include "Core/types.h"
#include "Core/Settings.h"

namespace Physics {
	class PhysicsManager;
}

namespace Renderer {
	namespace Input {
		class InputManager;
	}
}

namespace Game {

	class BaseScene {

	public:
		BaseScene(Physics::PhysicsManager& p_manager, Renderer::Input::InputManager& i_manager)
			: physicsManager(&p_manager)
			, inputmanager(&i_manager)
		{}
	protected:
		Observer<Physics::PhysicsManager> physicsManager;
		Observer <Renderer::Input::InputManager> inputmanager;
	};
}