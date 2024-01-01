#pragma once

#include "Core/types.h"
#include <array>
#include <variant>

namespace Core {
	struct Transform2D;
}

namespace Renderer::Geometry
{
	struct Point2Dc { float x; float y; };
	using Point2D = vec2;

	struct Direction {
		Direction() = default;
		Direction(const vec3& direction) noexcept;
		inline const vec3& operator()()const { return dir; }
		inline vec3 operator()() { return dir; }
	private:
		vec3 dir;
	};


	struct Ray {
		Point2D origin;
		Direction direction;
	};

	struct Line : public Ray {
		float length;
		const Point2D& GetDestPoint() const;
	};

	struct Rectangle {
		Rectangle() noexcept = default;
		Rectangle(const Point2D& tl, const Point2D& br) noexcept;
		Rectangle(const ::Core::Transform2D& transform) noexcept;
		Point2D topLeft{};
		Point2D botRight{};
		Point2D GetCenter()const;
		vec2 GetSizeFromCenter() const;
		std::array<Point2D, 4> GetCorners() const;
	};

}