#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Platform.png"));
	collisionOffset = sf::Vector2f(0, -50.0f);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
}
