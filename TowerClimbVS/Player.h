#pragma once
#include "SpriteObject.h"

class Player :
    public SpriteObject
{
public:
    Player();

    void Update(sf::Time frameTime) override;
    void UpdateAcceleration();

private:
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};