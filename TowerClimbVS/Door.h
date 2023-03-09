#pragma once
#include "SpriteObject.h"
class Door :
    public SpriteObject
{
public:
    Door();

protected:
    sf::Vector2f position;
};

