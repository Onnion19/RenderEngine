#include "GameObject/Block.h"
#include "Physics/PhysicsManager.h"

Game::Block::Block(Physics::PhysicsManager& manager, const vec3 position, const vec3& size)
	: quad(Core::Transform{ position, vec3 {0.f}, size })
	, collider(Core::Transform{ position, vec3 {0.f}, size })
{
	manager.RegisterCollider(collider);

	collider.RegisterOnCollideCallback([&](const vec3&) {
		manager.UnregisterCollider(collider);
	});
}

void Game::Block::SetColor(const Color& color)
{
	quad.SetColor(color);
}

const Game::Block::Color& Game::Block::GetColor() const
{
	return quad.GetColor();
}

void Game::Block::RegisterOnCollideCallback(Physics::Collider::CollisionCallback&& callback)
{
	collider.RegisterOnCollideCallback(std::move(callback));
}

void Game::Block::SetId(uint32 id)
{
	quadID = id;
}

uint32 Game::Block::GetId() const
{
	return quadID;
}
