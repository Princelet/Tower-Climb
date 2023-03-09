#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
	, position(500.0f, 450.0f)
{
	sprite.setTexture(AssetManager::RequestTexture("Platform.png"));
	sprite.setPosition(position);
}
