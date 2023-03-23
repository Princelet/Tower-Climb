#pragma once
#include "Platform.h"
class BreakingPlatform :
    public Platform
{
public:
    BreakingPlatform(sf::Vector2f newPosition);
    void HandleCollision(SpriteObject& other) override;
};

