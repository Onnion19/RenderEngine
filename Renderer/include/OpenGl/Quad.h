#pragma once

#include "Geometry/BasicShapes.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"
#include "Type/Color.h"
namespace Core {
	struct Transform;
}

namespace Renderer::GL {

	class BasicQuad {
	public: 
		using VBOTy = std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>;
		BasicQuad(const ::Core::Transform& transform, const Renderer::Type::RawColor& color = Renderer::Type::WHITE);
		std::array<Geometry::Point2D, 4> GetVertices()const;
		Renderer::Type::RawColor GetColor()const;

		std::vector<VBOTy> GetVBOData()const;
	private: 
		Geometry::Rectangle rect;
		Renderer::Type::RawColor quadColor;
	};
}