#include "Physics/PhysicsManager.h"
#include <algorithm>
#include "Core/RenderAssert.h"

namespace Physics {

	void PhysicsManager::RegisterCollider(Collider& collider)
	{
		RenderAssert(collider.colliderId == 0, "Collider already registered");
		collider.colliderId = ++nextColliderId;
		colliders.emplace_back(&collider);
	}

	void PhysicsManager::UnregisterCollider(const Collider& collider)
	{
		auto iter = std::find_if(colliders.begin(), colliders.end(), [=](const Collider* o) {return o->GetId() == collider.GetId(); });

		if (iter != colliders.end())
		{
			(*iter)->colliderId = 0;
			(*iter)->UnregisterCallbacks();
			colliders.erase(iter);
		}
	}

	bool PhysicsManager::SolveCollision(Collider& collider)
	{
		auto iter = std::find_if(colliders.begin(), colliders.end(), [=](const Collider* o) {return o->GetId() == collider.GetId(); });
		RenderAssert(iter != colliders.end(), "Collider not registered");

		for (auto& c : colliders)
		{
			auto& collider1 = *(*iter);
			auto& collider2 = *c;

			auto [hit, normal] = CollisionSolver::Solve(collider1, collider2);
			if (hit)
			{
				collider1.OnCollision(normal);
				collider2.OnCollision(normal);
				return true;
			}
		}

		return false;

	}
}
