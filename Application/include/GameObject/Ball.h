#pragma once

#include "Physics/MRU.h"
#include "Type/Transform.h"
#include "Physics/Collider.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/Quad.h"
#include "OpenGl/Program.h"


namespace Renderer::GL {
	class OrthoCamera;
}
namespace Physics {
	class PhysicsManager;
}
namespace Game
{

	class Ball {
	public:
		Ball(Physics::PhysicsManager& manager, const Renderer::GL::Program& shaderProgram, const vec3& position, float radius, float speed, const vec3& initialDirection = glm::normalize(vec3{ 0.1f, -0.9f,0.f }));
		~Ball();
		void Update(float deltaTime);
		void Draw();

	private:

		// Rendering
		void InitializeVAO();
	private:
		// Struct holding the values for the sdf data to send to the gpu
		struct SphereSDF {
			float center_x, center_y, radius;
		};

	private:
		Observer<Physics::PhysicsManager> physicsManager;
		float radius = 1.f;
		Physics::Collider collider;
		Physics::MRU mruObject;
		Core::Transform transform;

		// OpenGl data
		Renderer::GL::Program program;
		Renderer::GL::OpenGlBuffer< Renderer::Geometry::Point2D, SphereSDF> vbo;
		Renderer::GL::VertexAtributeObject vao;
		Renderer::GL::IndexBuffer ibo;

	};
}