#include "OpenGl/Quad.h"
#include "Type/Transform.h"

Renderer::GL::BasicQuad::BasicQuad(const ::Core::Transform2D& transform, const Renderer::Type::RawColor& color)
	: rect(transform), vbo(OpenGLUtils::Buffer::BufferType::ARRAY)
{
	InitializeVAO();
	SetPosition(transform, color);
}

void Renderer::GL::BasicQuad::SetPosition(const::Core::Transform2D& transform, const Renderer::Type::RawColor& color)
{
	std::vector<std::tuple<Geometry::Point2D, Renderer::Type::RawColor>> data;
	rect = { transform };
	auto points = rect.GetCorners();
	std::transform(points.begin(), points.end(), std::back_inserter(data), 
		[&](const Geometry::Point2D& point) -> std::tuple<Geometry::Point2D, Renderer::Type::RawColor> {
			return { point, color };
		});
	vbo.Insert(data);
	vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
	dirty = true;

}

void Renderer::GL::BasicQuad::Draw()
{
	vao.Bind();
	if (dirty)
	{
		dirty = false;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao.Unbind();
}

void Renderer::GL::BasicQuad::InitializeVAO()
{
	vao.Bind();
	// This attributes probably needs to be updated by shader or something
	vbo.Bind();
	Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
	Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Renderer::Type::RawColor> color{ 1,4, OpenGLUtils::Buffer::GLType::FLOAT, false };
	vao.EnableAndDefineAttributePointer(position);
	vao.EnableAndDefineAttributePointer(color);
	vao.Unbind();
}
