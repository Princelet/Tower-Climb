#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
{

	player.SetPosition(500.0f, 500.0f);
	platform.SetPosition(700.0f, 650.0f);
	door.SetPosition(700.0f, 500.0f);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	player.SetColliding(false);
	platform.SetColliding(false);
	door.SetColliding(false);

	if (player.CheckCollision(platform))
	{
		player.SetColliding(true);
		platform.SetColliding(true);
	}
	if (player.CheckCollision(door))
	{
		player.SetColliding(true);
		door.SetColliding(true);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
	door.Draw(target);
	platform.Draw(target);
}
