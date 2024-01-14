#include "Physics/PhysicsSolver.h"
#include "Physics/Collider.h"

namespace Physics::CollisionSolver {

	template<typename T1, typename T2>
	HitResult Solve_Internal(const T1& a, const T2& b)
	{
		return { false, vec3{0.f} };
	}

	template<>
	HitResult Solve_Internal< Renderer::Geometry::Rectangle, Renderer::Geometry::Rectangle>(const Renderer::Geometry::Rectangle& a, const Renderer::Geometry::Rectangle& b)
	{
		auto [a_width, a_height] = a.GetWidthHeight();
		auto [b_width, b_height] = a.GetWidthHeight();

		// verify if 
		bool collides = a.topLeft.x <= (b.topLeft.x + b_width) && // right edge 
			a.topLeft.x + a_width >= b.topLeft.x && // left edge
			a.botRight.y <= b.topLeft.y && //upper edge
			a.topLeft.y >= b.botRight.y; // down edge

		vec3 normal = (collides) ? vec3{ glm::normalize(b.GetCenter() - a.GetCenter()),0.f } : vec3{ 0.f };
		return { collides, normal };
	}

	template<>
	HitResult Solve_Internal< Renderer::Geometry::Circle, Renderer::Geometry::Circle>(const Renderer::Geometry::Circle& a, const Renderer::Geometry::Circle& b)
	{
		auto distance = (b.center - a.center);
		bool collides = distance.length() < (a.radius + b.radius);
		vec3 normal = (collides) ? glm::normalize(vec3{ distance, 0.f }) : vec3{ 0.f };
		return { collides, normal };
	}

	template<>
	HitResult Solve_Internal< Renderer::Geometry::Rectangle, Renderer::Geometry::Circle >(const Renderer::Geometry::Rectangle& rect, const Renderer::Geometry::Circle& circle)
	{

		auto [rect_width, rect_heigth] = rect.GetWidthHeight();
		auto rectCenter = rect.GetCenter();
		bool collision = false;

		float dx = fabsf(circle.center.x - rectCenter.x);
		float dy = fabsf(circle.center.y - rectCenter.y);

		if (dx > (rect_width / 2.0f + circle.radius)) return { false, vec3{0.f} };
		if (dy > (rect_heigth / 2.0f + circle.radius)) return { false, vec3{0.f} };



		if (dx > (rect_width / 2.0f) && dy > (rect_heigth / 2.0f))
		{
			float cornerDistanceSq = (dx - rect_width / 2.0f) * (dx - rect_width / 2.0f) +
				(dy - rect_heigth / 2.0f) * (dy - rect_heigth / 2.0f);

			collision = (cornerDistanceSq <= (circle.radius * circle.radius));
		}
		else
		{
			collision = true;
		}

		vec3 normal{ 0.f };

		if (collision)
		{
			if (circle.center.y > rect.topLeft.y)
			{
				normal = vec3(0.f, 1.f, 0.f);
			}
			else if (circle.center.y < rect.botRight.y)
			{
				normal = vec3(0.f, -1.f, 0.f);
			}
			else if (circle.center.x < rect.topLeft.x)
			{
				normal = vec3(-1.f, 0.f, 0.f);
			}
			else if (circle.center.x > rect.botRight.y){
				normal = vec3(1.f, 0.f, 0.f);
			}
			else {
				normal = vec3{ glm::normalize(circle.center - rectCenter),0.f };
			}
		}

		return {collision, normal};
	}

	template<>
	HitResult Solve_Internal< Renderer::Geometry::Circle, Renderer::Geometry::Rectangle>(const Renderer::Geometry::Circle& a, const Renderer::Geometry::Rectangle& b)
	{
		return Solve_Internal(b, a);
	}



	HitResult Solve(const Collider& a, const Collider& b)
	{
		using rectangle = Renderer::Geometry::Rectangle;
		using circle = Renderer::Geometry::Circle;

		auto& shapeA = a.GetShape();
		auto& shapeB = b.GetShape();

		if (std::holds_alternative<rectangle>(shapeA))
		{
			const rectangle& rectA = std::get<rectangle>(shapeA);
			if (std::holds_alternative<circle>(shapeB))
			{
				const circle& circleB = std::get<circle>(shapeB);
				return Solve_Internal(rectA, circleB);
			}
			else
			{
				const rectangle& rectB = std::get<rectangle>(shapeB);
				return Solve_Internal(rectA, rectB);
			}
		}
		else
		{
			const circle& circleA = std::get<circle>(shapeA);
			if (std::holds_alternative<circle>(shapeB))
			{
				const circle& circleB = std::get<circle>(shapeB);
				return Solve_Internal(circleA, circleB);
			}
			else
			{
				const rectangle& rectB = std::get<rectangle>(shapeB);
				return Solve_Internal(circleA, rectB);
			}
		}

	}




}
