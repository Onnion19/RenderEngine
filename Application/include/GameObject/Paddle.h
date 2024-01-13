#pragma once

#include "Core/types.h"
#include "Core/AliveToken.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Program.h"
#include "OpenGl/OpenGLUtils.h"
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

	struct PaddleRender {
	private:
		constexpr static auto vertexShaderPath = "Assets/Shaders/DefaultShader.vert";
		constexpr static auto fragmentShaderPath = "Assets/Shaders/DefaultShader.frag";
	public:
		Renderer::GL::IndexBuffer ibo{};
		Renderer::GL::VertexAtributeObject vao{};
		Renderer::GL::OpenGlBuffer<Renderer::Geometry::Point2D, Renderer::Type::RawColor> vbo{ OpenGLUtils::Buffer::BufferType::ARRAY };
		Renderer::GL::Shader vertexShader;
		Renderer::GL::Shader fragmentShader;
		Renderer::GL::Program program;
		const Core::Transform& transform;

		PaddleRender(const Core::Transform& trans)
			: transform(trans)
			, vertexShader(std::filesystem::path{ vertexShaderPath }, OpenGLUtils::Shader::Type::VERTEX)
			, fragmentShader(std::filesystem::path{ fragmentShaderPath }, OpenGLUtils::Shader::Type::FRAGMENT)
			, program(vertexShader, fragmentShader)
		{
			SetBuffers();
		}
		void SetBuffers()
		{
			// duplicated code, should be move to another object
			using VBOType = decltype(vbo)::bufferTy;
			vao.Bind();
			// Build VBO
			vbo.Bind();
			std::vector<VBOType> vboData;
			vboData.reserve(4);
			std::transform(Renderer::Geometry::NormalQuad::QuadVertices.begin(), Renderer::Geometry::NormalQuad::QuadVertices.end(), std::back_inserter(vboData), [](const vec2& vertice) ->  VBOType {return { vertice, Renderer::Type::RED }; });
			vbo.Insert(vboData);

			// Build IBO
			ibo.Bind();
			ibo.AddIndices(Renderer::Geometry::NormalQuad::QuadIndices);


			//Build VAO
			Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
			Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Type::RawColor> color{ 1,4, OpenGLUtils::Buffer::GLType::FLOAT, false };
			vao.EnableAndDefineAttributePointer(position);
			vao.EnableAndDefineAttributePointer(color);
			vao.Unbind();

			vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
			ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
		}
		void Draw(auto& camera)
		{
			program.UseProgram();
			program.SetUniformMatrix4("view", camera.GetCameraViewMatrix());
			program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());
			program.SetUniformMatrix4("model", static_cast<mat4>(transform));
			ibo.Bind();
			vao.Bind();
			const auto gltype = OpenGLUtils::EnumToGLEnum(OpenGLUtils::Buffer::GLType::UNSIGNED_INT);
			glDrawElements(GL_TRIANGLES, static_cast<uint32>(ibo.size()), gltype, nullptr);
			vao.Unbind();
		}

	};


	class Paddle {

	public:
		Paddle(Renderer::Input::InputManager& inputManager, Physics::PhysicsManager& physicsManager, const vec3& position, float length, float speed);
		void update(float deltatime);
		void Draw(auto& camera)
		{
			renderer.Draw(camera);
		}
	private:
		Renderer::Core::TokenOwner inputToken;
		Core::Transform transform;
		PaddleRender renderer;
		Physics::Collider collider;
		Physics::MRU movementData;

	};
}