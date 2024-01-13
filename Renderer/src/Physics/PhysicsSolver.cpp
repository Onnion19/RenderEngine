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
	HitResult Solve_Internal< Renderer::Geometry::Rectangle, Renderer::Geometry::Circle >(const Renderer::Geometry::Rectangle& a, const Renderer::Geometry::Circle& b)
	{

		auto [a_width, a_height] = a.GetWidthHeight();
		auto center = a.GetCenter();
		bool collision = false;

		float dx = fabsf(b.center.x - center.x);
		float dy = fabsf(b.center.y - center.y);

		if (dx > (a_width / 2.0f + b.radius)) return { false, vec3{0.f} };
		if (dy > (a_height / 2.0f + b.radius)) return { false, vec3{0.f} };



		if (dx > (a_width / 2.0f) && dy > (a_height / 2.0f))
		{
			float cornerDistanceSq = (dx - a_width / 2.0f) * (dx - a_width / 2.0f) +
				(dy - a_height / 2.0f) * (dy - a_height / 2.0f);

			collision = (cornerDistanceSq <= (b.radius * b.radius));
		}

		vec3 normal = (collision) ? vec3{ glm::normalize(b.center - center), 0.f } : vec3{ 0.f };

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
