#include "OpenGl/Quad.h"
#include "Type/Transform.h"
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>

Renderer::GL::BasicQuad::BasicQuad(const ::Core::Transform& t, const Renderer::Type::ColorRGBA& color)
	: _transform(t), quadColor(color)
{}

std::array<Renderer::Geometry::Point2D, 4> Renderer::GL::BasicQuad::GetVertices() const
{
	return Geometry::Rectangle(_transform).GetCorners();
}

void Renderer::GL::BasicQuad::SetColor(const Renderer::Type::ColorRGBA& color)
{
	quadColor = color;
}

const Renderer::Type::ColorRGBA& Renderer::GL::BasicQuad::GetColor() const
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
	
