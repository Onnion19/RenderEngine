#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsSolver.h"
#include "Core/RenderAssert.h"
#include <algorithm>

namespace Physics {

	void PhysicsManager::RegisterCollider(Collider& collider)
	{
		RenderAssert(collider.colliderId == 0, "Collider already registered");
		collider.colliderId = ++nextColliderId;
		colliders.emplace_back(&collider);
	}

	void PhysicsManager::UnregisterCollider(const Collider& collider)
	{
		if (collider.colliderId != 0)
		{
			colliderToRemove.emplace_back(collider.colliderId);
		}

	}

	bool PhysicsManager::SolveCollision(Collider& collider)
	{
		RemoveColliders();
		auto iter = std::find_if(colliders.begin(), colliders.end(), [=](const Collider* o) {return o->GetId() == collider.GetId(); });
		RenderAssert(iter != colliders.end(), "Collider not registered");

		for (auto& c : colliders)
		{
			if (collider.colliderId == c->colliderId) continue;

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
	void PhysicsManager::RemoveColliders()
	{
		for (const auto& colliderID : colliderToRemove)
		{
			auto iter = std::find_if(colliders.begin(), colliders.end(), [=](const Collider* o) {return o->GetId() == colliderID; });
			RenderAssert(iter != colliders.end(), "Trying to remove a collider that does not exist");
			(*iter)->colliderId = 0;
			(*iter)->UnregisterCallbacks();
			colliders.erase(iter);
		}

		colliderToRemove.clear();
	}
}
