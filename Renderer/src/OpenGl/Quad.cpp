#include "OpenGl/Quad.h"
#include "Type/Transform.h"
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>
#include <ranges>

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

	auto zipFunc = [=](auto vertex, auto uv) -> VBOTy { return { vertex, uv, color }; };

	auto zip = std::views::zip_transform(zipFunc, vertices, Geometry::NormalQuad::QuadUV);
	std::transform(zip.begin(), zip.end(), std::back_inserter(data), [&](auto tuple) -> VBOTy {return tuple; });

	return data;
}

