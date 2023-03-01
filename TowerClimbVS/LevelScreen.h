#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
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
	sf::Sprite tempSpr;
};

