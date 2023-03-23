#pragma once
#include "Platform.h"
class MovingPlatform :
    public Platform
{
public:
    MovingPlatform( float newSpeed, sf::Vector2f newPos1, sf::Vector2f newPos2);
    void Update(sf::Time frameTime) override;

private:
    const float SPEED;
    const sf::Vector2f POS1;
    const sf::Vector2f POS2;
    const sf::Vector2f* targetPoint;
    sf::Vector2f velocity;
};

