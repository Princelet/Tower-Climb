#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Door.png"));
	collisionOffset = sf::Vector2f(0.0f, 9.75f);
	collisionScale = sf::Vector2f(0.4f, 0.85f);
}
