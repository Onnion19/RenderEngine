#include "OpenGL/QuadRenderer.h"

#include <ranges>
#include "OpenGl/TextureLoader.h"

namespace Renderer::GL
{
	void Renderer::GL::QuadRenderer::Draw()
	{
		program.UseProgram();
		program.SetUniformMatrix4("model", static_cast<mat4>(transform));
		if (texture)
			texture->Bind();

		ibo.Bind();
		vao.Bind();
		const auto gltype = OpenGLUtils::EnumToGLEnum(OpenGLUtils::Buffer::GLType::UNSIGNED_INT);
		glDrawElements(GL_TRIANGLES, static_cast<uint32>(ibo.size()), gltype, nullptr);
		vao.Unbind();
	}

	void QuadRenderer::SetBuffers()
	{
		using VBOType = decltype(vbo)::bufferTy;
		vao.Bind();

		vbo.Bind();
		std::vector<VBOType> vboData;
		vboData.reserve(4);
		auto zipFunc = [=](auto vertex, auto uv) -> VBOType { return { vertex,  uv, Type::WHITE, }; };
		auto zip = std::views::zip_transform(zipFunc, Geometry::NormalQuad::QuadVertices, Geometry::NormalQuad::QuadUV);
		std::transform(zip.begin(), zip.end(), std::back_inserter(vboData), [&](auto tuple) -> VBOType {return tuple; });
		vbo.Insert(vboData);

		// Build IBO
		ibo.Bind();
		ibo.AddIndices(Renderer::Geometry::NormalQuad::QuadIndices);


		//Build VAO
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Geometry::UVCoordinates> uvs{ 1,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
		Renderer::GL::VertexAtributeObject::AttributePointer<VBOType, Renderer::Type::RawColor> color{ 2,4, OpenGLUtils::Buffer::GLType::FLOAT, false };
		vao.EnableAndDefineAttributePointer(position);
		vao.EnableAndDefineAttributePointer(uvs);
		vao.EnableAndDefineAttributePointer(color);
		vao.Unbind();

		vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
		ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
	}

	void QuadRenderer::LoadTexture(std::string_view texturePath)
	{
		if (texturePath.empty()) return;

		auto data = ImageLoader::LoadTexture(texturePath);
		RenderAssert(data, data.error().c_str());
		texture = std::make_unique<Renderer::GL::Texture>(*data);
		//ImageLoader::FreeTexture(*data);
	}

}