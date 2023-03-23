#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Door"));
	collisionOffset = sf::Vector2f(0.0f, 10.5f);
	collisionScale = sf::Vector2f(0.44f, 0.85f);
}
