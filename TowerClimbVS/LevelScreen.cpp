#include <fstream>
#include <iostream>
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
	, currentLevel(1)
{
	LoadLevel(1);
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

bool LevelScreen::LoadNextLevel()
{
	return LoadLevel(++currentLevel);
}

void LevelScreen::Restart()
{
	LoadLevel(currentLevel);
}

bool LevelScreen::LoadLevel(int number)
{
	// Construct level name from number
	std::string name = "Level" + std::to_string(number);
	bool success = LoadLevel(name);

	if (success)
		currentLevel = number;

	return success;
}

bool LevelScreen::LoadLevel(std::string file)
{
	// Open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/" + file + ".txt";

	inFile.open(filePath);


	// Make sure the file was actually opened
	if (!inFile)
	{
		// File was not opened
		return false;
	}

	// Delete before clearing!
	for (size_t i = 0; i < platforms.size(); ++i)
	{
		delete platforms[i];
		platforms[i] = nullptr;
	}

	platforms.clear();


	// Set the starting x and y coordinates used to position our level objects
	float x = 0.0f;
	float y = 0.0f;

	// Define the spacing we will use for our grid
	const float X_SPACE = 150.0f;
	const float Y_SPACE = 150.0f;


	// Read each character one by one...
	char ch;

	// Each time, try to read the next character
	// If successful, execute the body of the loop

	// The "noskipws" means we include white space (spaces/newlines)
	while (inFile >> std::noskipws >> ch)
	{
		// Perform action based on what was read in
		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0.0f;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}
		else if (ch == 'N')
		{
			platforms.push_back(new Platform(sf::Vector2f(x, y)));
		}
		else if (ch == 'B')
		{
			platforms.push_back(new BreakingPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'M')
		{
			platforms.push_back(new MovingPlatform(200.0f, sf::Vector2f(0, y), sf::Vector2f(gamePointer->GetWindow()->getSize().x, y)));
		}
		else if (ch == 'D')
		{
			platforms.push_back(new DeadlyPlatform(sf::Vector2f(x, y)));
		}
		else if (ch == 'O')
		{
			door.SetPosition(x, y);
		}
		else if (ch == '-')
		{
			// Do nothing - empty space
		}
		else
		{
			std::cerr << "Unrecognised character in level file: " << ch;
		}
	}

	// Close the file since we're done
	inFile.close();

	// Set game to start
	gameRunning = true;

	// Return true since we successfully loaded the file
	return true;
}
