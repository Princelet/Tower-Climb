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
	, camera()
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

		if (player.GetPosition().x < 0)
		{
			player.SetPosition(1, player.GetPosition().y);
		}
		/*
		if (player.GetPosition().x > )
		{
			player.SetPosition(1, player.GetPosition().y);
		}
		*/

		if (player.GetPosition().y > 2000)
		{
			endPanel.Update(frameTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				Restart();
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
	// Update camera based on the render target size and player position
	camera = target.getDefaultView();
	sf::Vector2f cameraPos = camera.getCenter();
	cameraPos.y = player.GetPosition().y + 100;
	camera.setCenter(cameraPos);

	// Update render target to use camera
	target.setView(camera);


	// Draw "world" objects (use camera)
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}

	door.Draw(target);
	player.Draw(target);


	// For any UI, reset camera to default view before drawing
	target.setView(target.getDefaultView());

	// Draw UI objects (use base view)
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
