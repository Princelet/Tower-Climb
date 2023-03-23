#pragma once
#include "Platform.h"
class DeadlyPlatform :
    public Platform
{
public:
    DeadlyPlatform(sf::Vector2f newPosition);
    void HandleCollision(SpriteObject& other) override;
};

