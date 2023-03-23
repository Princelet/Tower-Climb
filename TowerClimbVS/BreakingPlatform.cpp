#include "BreakingPlatform.h"
#include "AssetManager.h"

BreakingPlatform::BreakingPlatform(sf::Vector2f newPosition)
	: Platform(newPosition)
{
	sprite.setTexture(AssetManager::RequestTexture("BreakingPlatform"));
}

void BreakingPlatform::HandleCollision(SpriteObject& other)
{
	alive = false;
}
