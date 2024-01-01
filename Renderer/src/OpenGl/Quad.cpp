#include "OpenGl/Quad.h"
#include "Type/Transform.h"

Renderer::GL::BasicQuad::BasicQuad(const ::Core::Transform2D& transform, const Renderer::Type::RawColor& /*color*/)
	: rect(transform), vbo(OpenGLUtils::Buffer::BufferType::ARRAY)
{
	InitializeVAO();
	SetPosition(transform);
}

void Renderer::GL::BasicQuad::SetPosition(const::Core::Transform2D& transform)
{
	rect = { transform };
	auto points = rect.GetCorners();
	vbo.Insert(points);
	vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
	dirty = true;

}

void Renderer::GL::BasicQuad::Draw()
{
	vbo.Bind();
	vao.Bind();
	if (dirty)
	{
	
		dirty = false;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao.Unbind();
	vbo.Unbind();
}

void Renderer::GL::BasicQuad::InitializeVAO()
{
	vbo.Bind();
	vao.Bind();
	Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Geometry::Point2D> properties{ 0 ,3, OpenGLUtils::Buffer::GLType::FLOAT, false };
	vao.EnableAndDefineAttributePointer(properties);
}
