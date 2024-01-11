#pragma once

#include "Geometry/BasicShapes.h"
#include "Type/Color.h"
#include "Type/Transform.h"


namespace Renderer::GL {

	class BasicQuad {
	public:
		using VBOTy = std::tuple<Renderer::Geometry::Point2D, Renderer::Type::RawColor>;

		BasicQuad(const ::Core::Transform& transform, const Renderer::Type::ColorRGBA& color = Renderer::Type::WHITE);
		std::array<Geometry::Point2D, 4> GetVertices()const;
		void SetColor(const Renderer::Type::ColorRGBA& color);
		const Renderer::Type::ColorRGBA& GetColor()const;
		std::vector<VBOTy> GetVBOData()const;

		::Core::Transform& operator->() { return _transform; }
		const ::Core::Transform& operator->() const { return _transform; }
	private:
		Renderer::Type::ColorRGBA quadColor;
		::Core::Transform _transform;
	};
}