#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
{
	player.SetPosition(500.0f, 500.0f);
	platform.SetPosition(500.0f, 650.0f);
	door.SetPosition(500.0f, 500.0f);
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
		player.HandleCollision(platform);
	}
	if (player.CheckCollision(door))
	{
		player.SetColliding(true);
		door.SetColliding(true);
	}

	if (player.GetPosition().y > 2000)
	{
		player.SetPosition(500.0f, 500.0f);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	door.Draw(target);
	platform.Draw(target);

	player.Draw(target);
}
