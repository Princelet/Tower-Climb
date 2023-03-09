#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
#include "Door.h"
#include "AssetManager.h"

class Game;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePointer);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

private:
	Player player;
	Door door;
	Platform platform;
};

