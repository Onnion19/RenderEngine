#pragma once

#include "Core/types.h"
#include "Core/AliveToken.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Program.h"
#include "OpenGl/OpenGLUtils.h"
#include "OpenGl/QuadRenderer.h"
#include "Geometry/BasicShapes.h"
#include "Type/Color.h"
#include "Type/Transform.h"
#include "Physics/Collider.h"
#include "Physics/MRU.h"


namespace Renderer::Input {
	class InputManager;
}

namespace Physics {
	class PhysicsManager;
}

namespace Game
{
	class Paddle {
		constexpr static auto vertexShaderPath = "Assets/Shaders/PaddelShader.vert";
		constexpr static auto fragmentShaderPath = "Assets/Shaders/PaddelShader.frag";
		constexpr static auto texturePath = "Assets/Textures/Block.png";
	public:
		Paddle(Renderer::Input::InputManager& inputManager, Physics::PhysicsManager& physicsManager, auto& camera, const vec3& position, float length, float speed)
			: transform({ position, vec3{},vec3{length, 45.f, 1.f} })
			, renderer(transform, camera, vertexShaderPath, fragmentShaderPath, texturePath)
			, collider(Renderer::Geometry::Rectangle(transform))
			, movementData({ vec3{}, speed })
		{
			Init(inputManager, physicsManager);
		}

		const Physics::Collider&  GetCollider()const { return collider; }
		void update(float deltatime);
		void Draw();
	private: 
		void Init(Renderer::Input::InputManager& inputManager, Physics::PhysicsManager& physicsManager);
	private:
		Renderer::Core::TokenOwner inputToken;
		Core::Transform transform;
		Renderer::GL::QuadRenderer renderer;
		Physics::Collider collider;
		Physics::MRU movementData;

	};
}