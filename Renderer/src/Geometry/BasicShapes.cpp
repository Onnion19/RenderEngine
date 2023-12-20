#include "Geometry/BasicShapes.h"
#include "Type/Transform.h"

namespace Renderer::Geometry {

	Direction::Direction(const vec3& direction) noexcept
		: dir(glm::normalize(direction))
	{}

	inline const Point2D& Line::GetDestPoint() const
	{
		return origin + vec2(direction()) * length;
	}

	Rectangle::Rectangle(const Point2D& tl, const Point2D& br) noexcept
		: topLeft(tl)
		, botRight(br)
	{}

	Rectangle::Rectangle(const::Core::Transform2D& transform) noexcept
		: topLeft(transform.position.x - transform.size.x, transform.position.y + transform.size.y)
		, botRight(transform.position.x + transform.size.x, transform.position.y - transform.size.y)
	{}

	Point2D Rectangle::GetCenter() const
	{
		auto size = GetSizeFromCenter();
		return { topLeft.x + size.x, topLeft.y - size.y };
	}

	vec2 Rectangle::GetSizeFromCenter() const
	{
		return vec2{ botRight.x - topLeft.x, topLeft.y - botRight.y } / 2.f;
	}

}
