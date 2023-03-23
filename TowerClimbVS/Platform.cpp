#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Platform.png"));
	collisionOffset = sf::Vector2f(0, -55.0f);
	collisionScale = sf::Vector2f(1.0f, 0.25f);
}
