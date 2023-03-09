#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
	, position(500.0f, 300.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("Door.png"));
	sprite.setPosition(position);
}
