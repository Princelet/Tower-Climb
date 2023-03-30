#include "Door.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Door::Door(LevelScreen* newLevelScreen)
	: SpriteObject()
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Door"));
	collisionOffset = sf::Vector2f(0.0f, 10.5f);
	collisionScale = sf::Vector2f(0.44f, 0.85f);
}

void Door::HandleCollision(SpriteObject& other)
{
	levelScreen->TriggerEndState(true);
	SpriteObject::HandleCollision(other);
}
