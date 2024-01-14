#pragma once

#include "Core/types.h"
#include "Type/Transform.h"


namespace Physics {

	struct MRU {
		vec3 direction;
		float speed;
		[[nodiscard]] vec3 Apply(float deltaTime)
		{
			return direction * speed * deltaTime / 1000.f;
		}
		void Apply(float deltaTime, vec3& positionToUpdate)
		{
			positionToUpdate += Apply(deltaTime);
		}
	};
}