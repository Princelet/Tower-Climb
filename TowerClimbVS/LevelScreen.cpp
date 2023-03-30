#include "LevelScreen.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"
#include "EndPanel.h"
#include "Game.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, door(this)
	, platforms()
	, endPanel(newGamePointer->GetWindow(), "YOU WIN", "Press R to Restart\nor Esc to Exit")
	, gameRunning(true)
{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player.Update(frameTime);
		player.SetColliding(false);
		door.SetColliding(false);

		for (size_t i = 0; i < platforms.size(); ++i)
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
			door.HandleCollision(player);
		}

		if (player.GetPosition().y > 2000)
		{
			player.SetPosition(500.0f, 500.0f);
		}
	}
	else
	{
		endPanel.Update(frameTime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Restart();
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}

	door.Draw(target);
	player.Draw(target);

	if (!gameRunning)
	{
		endPanel.Draw(target);
	}
}

void LevelScreen::TriggerEndState(bool win)
{
	gameRunning = false;
	endPanel.StartAnimation();
}

void LevelScreen::Restart()
{
	player.SetPosition(500.0f, 500.0f);

	// Delete before clearing!
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}

	platforms.clear();
	platforms.push_back(new Platform(sf::Vector2f(500.0f, 650.0f)));
	platforms.push_back(new Platform(sf::Vector2f(900.0f, 900.0f)));
	platforms.push_back(new MovingPlatform(100.0f, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(1000.0f, 700.0f)));
	platforms.push_back(new BreakingPlatform(sf::Vector2f(1100.0f, 650.0f)));
	platforms.push_back(new DeadlyPlatform(sf::Vector2f(1200.0f, 400.0f)));

	door.SetPosition(900.0f, 750.0f);

	gameRunning = true;
}
