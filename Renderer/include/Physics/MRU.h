#pragma once

#include "Core/types.h"

namespace Core
{
	struct Transform;
}

namespace Physics {

	struct MRU {
		vec3 direction; 
		float speed;
		vec3 Apply(float deltaTime);
		void Apply(float deltaTime, Core::Transform& transform);
	};
}