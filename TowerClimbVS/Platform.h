#pragma once
#include "SpriteObject.h"
class Platform :
    public SpriteObject
{
public:
    Platform();

private:
    sf::Vector2f position;
};

