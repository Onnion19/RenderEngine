#include "GameObject/Powerup.h"
#include "GameObject/PostProcessActor.h"
#include "Physics/PhysicsSolver.h"
namespace Game {
	bool PowerUp::IsActive() const
	{
		return active;
	}
	void PowerUp::Update(float deltaTime)
	{
		if (!active) return;
		movementData.Apply(deltaTime, transform.position);
		collider.UpdateShape(Renderer::Geometry::Rectangle(transform));

		auto [hit, normal]  = Physics::CollisionSolver::Solve(paddleActor.GetCollider(), collider);
		active = !hit;

		if (transform.position.y < 0)
		{
			active = false;
			if (postProcessActor)
				postProcessActor->ActivateEffect(2.5f);
		}
	}

	void PowerUp::Draw()
	{
		if (!active) return;
		renderer.Draw();
	}

	void PowerUp::ActivatePowerUP(const vec3& newPosition)
	{
		transform.position = newPosition;
		active = true;
	}
}
