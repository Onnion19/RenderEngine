#include "Physics/MRU.h"
#include "Type/Transform.h"

namespace Physics {

	vec3 Physics::MRU::Apply(float deltaTime)
	{
		return direction * speed * deltaTime;
	}

	void Physics::MRU::Apply(float deltaTime, Core::Transform& transform)
	{
		transform.position += Apply(deltaTime);
	}

}

