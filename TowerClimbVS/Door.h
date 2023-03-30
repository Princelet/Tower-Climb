#pragma once
#include "SpriteObject.h"

class LevelScreen;

class Door :
    public SpriteObject
{
public:
    Door(LevelScreen* newLevelScreen);
    void HandleCollision(SpriteObject& other) override;

private:
    LevelScreen* levelScreen;
};

