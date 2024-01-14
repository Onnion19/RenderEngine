#pragma once

#include "Core/types.h"
#include "Core/AliveToken.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Program.h"
#include "OpenGl/OpenGLUtils.h"
#include "OpenGl/Texture.h"
#include "OpenGl/QuadRenderer.h"
#include "Type/Color.h"
#include "Type/Transform.h"
#include "Physics/Collider.h"
#include "Physics/MRU.h"
#include "GameObject/Paddle.h"

namespace Game {
	class PostProcessor;

	class PowerUp {
		constexpr static auto vertexShaderPath = "Assets/Shaders/DefaultShader.vert";
		constexpr static auto fragmentShaderPath = "Assets/Shaders/DefaultShader.frag";
		constexpr static auto texturePath = "Assets/Textures/PowerUp.png";
	public:
		PowerUp(Observer<PostProcessor> postProcess, Paddle& paddle, auto& camera, const vec3& startingPosition, float speed)
			: postProcessActor(postProcess)
			, paddleActor(paddle)
			, transform({ startingPosition, vec3{}, vec3{50.f, 35.f, 1.f} })
			, collider(Renderer::Geometry::Rectangle(transform))
			, renderer(transform, camera, vertexShaderPath, fragmentShaderPath)
			, movementData({ vec3{0.f, -1.f, 0.f} , speed }) {}

		bool IsActive() const;
		void Update(float deltaTime);
		void Draw();
		void ActivatePowerUP(const vec3& position);
	private:

		Observer<PostProcessor> postProcessActor;
		Paddle& paddleActor;
		Core::Transform transform;
		Physics::Collider collider;
		Renderer::GL::QuadRenderer renderer;
		Physics::MRU movementData;
		std::unique_ptr<Renderer::GL::Texture> texture;
		bool active = true;

	};
}

