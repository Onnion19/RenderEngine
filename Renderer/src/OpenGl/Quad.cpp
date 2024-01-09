#include "OpenGl/Quad.h"
#include "Type/Transform.h"

Renderer::GL::BasicQuad::BasicQuad(const ::Core::Transform& transform, const Renderer::Type::RawColor& color)
	: rect(transform), quadColor(color)
{}

std::array<Renderer::Geometry::Point2D, 4> Renderer::GL::BasicQuad::GetVertices() const
{
	return rect.GetCorners();
}

Renderer::Type::RawColor Renderer::GL::BasicQuad::GetColor() const
{
	return quadColor;
}

std::vector<Renderer::GL::BasicQuad::VBOTy> Renderer::GL::BasicQuad::GetVBOData() const
{
	std::vector<VBOTy> data;
	data.reserve(4);
	auto vertices = GetVertices();
	auto color = GetColor();
	std::transform(vertices.begin(), vertices.end(), std::back_inserter(data), [&](const Geometry::Point2D& vertice) -> VBOTy {return { vertice, color }; });

	return data;
}
	
