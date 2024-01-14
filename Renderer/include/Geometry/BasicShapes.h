#pragma once

#include "Core/types.h"
#include <array>
#include <variant>

namespace Core {
	struct Transform;
}

namespace Renderer::Geometry
{

	using Point2D = vec2;

	struct UVCoordinates
	{
		float x, y;
	};

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
		Rectangle(const ::Core::Transform& transform) noexcept;
		Point2D GetCenter()const;
		vec2 GetSizeFromCenter() const;
		std::array<Point2D, 4> GetCorners() const;
		std::tuple<float, float> GetWidthHeight()const noexcept;

		Point2D topLeft{};
		Point2D botRight{};
	};

	struct Circle {
		Circle() noexcept = default;
		Circle(const vec2& center, float radius) noexcept;

		float radius;
		vec2 center;
	};


	namespace NormalQuad {
		// QUAD Vertices
		constexpr std::array<Renderer::Geometry::Point2D, 4> QuadVertices{
			vec2 {-0.5f, 0.5f} ,//TL
			vec2{0.5f,0.5f}, //TR
			vec2{0.5f, -0.5f},  //BR
			vec2{-0.5f, -0.5f} //BL
		};

		//Quad Indices
		constexpr std::array<uint8, 6> QuadIndices{
			2,1,0,
			0,3,2
		};

		//UV Coordinates
		constexpr std::array<UVCoordinates, 4> QuadUV{
			UVCoordinates{0,1}, //TL
			UVCoordinates{1,1},	//TR
			UVCoordinates{1,0}, //BR
			UVCoordinates{0,0}	//BL
		};
	}


}