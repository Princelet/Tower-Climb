#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class Game;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;


private:
    sf::Texture tempTex;
    sf::Sprite tempSpr;
};

