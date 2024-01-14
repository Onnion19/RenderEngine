#pragma once 
#include "Core/types.h"
#include "Core/AliveToken.h"
#include "OpenGl/VertexAttributeObject.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/Program.h"
#include "OpenGl/OpenGLUtils.h"
#include "OpenGl/Texture.h"
#include "Geometry/BasicShapes.h"
#include "Type/Color.h"
#include "Type/Transform.h"
#include "Physics/Collider.h"
#include "Physics/MRU.h"

namespace Renderer::GL
{
	class QuadRenderer {
	public:
		QuadRenderer(const ::Core::Transform& trans, auto& camera, std::string_view vertexshader, std::string_view fragmentshader, std::string_view texturePath = {})
			: transform(trans)
		{
			makeProgram(vertexshader, fragmentshader, camera);
			SetBuffers();
			LoadTexture(texturePath);
		}
		void Draw();

	private:
		void makeProgram(std::string_view vertexshader, std::string_view fragmentshader, auto& camera)
		{
			std::filesystem::path vertex{ vertexshader };
			std::filesystem::path fragment{ fragmentshader };
			Renderer::GL::Shader vs(vertex, OpenGLUtils::Shader::Type::VERTEX);
			Renderer::GL::Shader fs(fragment, OpenGLUtils::Shader::Type::FRAGMENT);
			program = { vs, fs };
			program.SetUniformMatrix4("model", glm::identity<mat4>());
			program.SetUniformMatrix4("view", camera.GetViewMatrix());
			program.SetUniformMatrix4("projection", camera.GetProjectionMatrix());
		}
		void SetBuffers();

		void LoadTexture(std::string_view texturePath);
	private:
		Renderer::GL::IndexBuffer ibo{};
		Renderer::GL::VertexAtributeObject vao{};
		Renderer::GL::OpenGlBuffer<Renderer::Geometry::Point2D, Renderer::Geometry::UVCoordinates, Renderer::Type::RawColor> vbo{ OpenGLUtils::Buffer::BufferType::ARRAY };
		Renderer::GL::Program program;
		std::unique_ptr<Renderer::GL::Texture> texture;
		const ::Core::Transform& transform;
	};
}
