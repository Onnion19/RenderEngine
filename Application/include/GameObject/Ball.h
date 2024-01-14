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
		void Draw(auto& camera) 
		{
			using VBOType = decltype(vbo)::bufferTy;
			std::vector<VBOType> vboData;
			vbo.clear();
			vboData.reserve(4);
			std::transform(Renderer::Geometry::NormalQuad::QuadVertices.begin(), Renderer::Geometry::NormalQuad::QuadVertices.end(), std::back_inserter(vboData), [=](const vec2& vertice) ->  VBOType {return { vertice, {transform.position.x, transform.position.y, radius} }; });
			vbo.Insert(vboData);
			vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::DYNAMIC_DRAW);

			program.UseProgram();
			program.SetUniformMatrix4("view", camera.GetCameraViewMatrix());
			program.SetUniformMatrix4("model", static_cast<mat4>(transform));
			ibo.Bind();
			vao.Bind();
			const auto gltype = OpenGLUtils::EnumToGLEnum(OpenGLUtils::Buffer::GLType::UNSIGNED_INT);
			glDrawElements(GL_TRIANGLES, static_cast<uint32>(ibo.size()), gltype, nullptr);
			vao.Unbind();
		}

	private:

		// Rendering
		void InitializeVAO();
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