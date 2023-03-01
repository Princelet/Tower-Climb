#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, tempTex()
	, tempSpr()
{
	tempTex.loadFromFile("Assets/Graphics/PlayerStand.png");
	tempSpr.setTexture(tempTex);
}

void LevelScreen::Update(sf::Time frameTime)
{
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
}
