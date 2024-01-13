#pragma once

#include <vector>
#include "Physics/Collider.h"
#include "Physics/PhysicsSolver.h"

namespace Physics {

	class PhysicsManager
	{
	public: 
		using colliderID = unsigned int;
		PhysicsManager() = default; 

		void RegisterCollider(Collider& collider);
		void UnregisterCollider(const Collider& collider);

		bool SolveCollision(Collider& collider);

	private: 
		std::vector<Collider*> colliders;
		colliderID nextColliderId = 0;
	};
}