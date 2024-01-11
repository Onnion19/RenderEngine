#include "GameObject/Block.h"

Game::Block::Block(const vec3 position, const vec3& size)
	: quad(Core::Transform{ position, vec3 {0.f}, size })
{
}

void Game::Block::SetColor(const Color& color)
{
	quad.SetColor(color);
}

const Game::Block::Color& Game::Block::GetColor() const
{
	return quad.GetColor();
}

void Game::Block::SetId(uint32 id)
{
	quadID = id;
}

uint32 Game::Block::GetId() const
{
	return quadID;
}
