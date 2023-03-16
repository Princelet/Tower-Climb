#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Door.png"));
	collisionOffset = sf::Vector2f(0, 20.0f);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
}
