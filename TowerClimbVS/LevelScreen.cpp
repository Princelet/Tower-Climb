#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
{
	tempSpr.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
}

void LevelScreen::Update(sf::Time frameTime)
{
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
}
