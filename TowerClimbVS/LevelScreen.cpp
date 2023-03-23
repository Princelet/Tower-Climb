#include "LevelScreen.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platforms()
	, door()
{
	player.SetPosition(500.0f, 500.0f);

	platforms.push_back(new Platform(sf::Vector2f(500.0f, 650.0f)));
	platforms.push_back(new MovingPlatform(100.0f, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(1000.0f, 700.0f)));
	platforms.push_back(new BreakingPlatform(sf::Vector2f(1100.0f, 650.0f)));
	platforms.push_back(new DeadlyPlatform(sf::Vector2f(1200.0f, 400.0f)));

	door.SetPosition(500.0f, 500.0f);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	player.SetColliding(false);
	door.SetColliding(false);

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Update(frameTime);
		platforms[i]->SetColliding(false);

		if (platforms[i]->CheckCollision(player))
		{
			player.SetColliding(true);
			platforms[i]->SetColliding(true);
			player.HandleCollision(*platforms[i]);
			platforms[i]->HandleCollision(player);
		}
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
	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}

	door.Draw(target);
	player.Draw(target);
}
