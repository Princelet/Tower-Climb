#pragma once
#include "Platform.h"
class BreakingPlatform :
    public Platform
{
public:
    BreakingPlatform();
    void Update(sf::Time frameTime) override;
};

