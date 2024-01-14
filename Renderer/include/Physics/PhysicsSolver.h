#pragma once

#include "Core/types.h"
#include <tuple>

namespace Physics
{
	class Collider; 

	using HitResult = std::tuple<bool, vec3>;
	namespace CollisionSolver 
	{

		HitResult Solve(const Collider& a, const Collider& b);

	}
}