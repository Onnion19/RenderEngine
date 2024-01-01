#pragma once

#include "Geometry/BasicShapes.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"
#include "Type/Color.h"
namespace Core {
	struct Transform2D;
}

namespace Renderer::GL {

	class BasicQuad {
	public: 
		BasicQuad(const ::Core::Transform2D& transform, const Renderer::Type::RawColor& color = Renderer::Type::WHITE);
		void SetPosition(const ::Core::Transform2D& transform);
		void Draw();

	private: 
		void InitializeVAO();
	private: 
		Geometry::Rectangle rect;
		OpenGlBuffer < Geometry::Point2D> vbo;
		VertexAtributeObject vao;
		bool dirty = true;

	};
}