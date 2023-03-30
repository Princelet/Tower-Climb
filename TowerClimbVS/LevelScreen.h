#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "AssetManager.h"
#include "EndPanel.h"

class Game;
class Platform;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePointer);

	void Update(sf::Time frameTime);
	void Draw(sf::RenderTarget& target);

	void TriggerEndState(bool win);

private:
	void Restart();

	Player player;
	Door door;
	std::vector<Platform*> platforms;
	EndPanel endPanel;
	bool gameRunning;
};