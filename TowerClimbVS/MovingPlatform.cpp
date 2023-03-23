#include "MovingPlatform.h"
#include "AssetManager.h"
#include "VectorHelper.h"

MovingPlatform::MovingPlatform(float newSpeed, sf::Vector2f newPos1, sf::Vector2f newPos2)
	: Platform()
	, SPEED(newSpeed)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity (0, 0)
{
	sprite.setTexture(AssetManager::RequestTexture("MovingPlatform"));
}

void MovingPlatform::Update(sf::Time frameTime)
{
	float frameSeconds = frameTime.asSeconds();
	sf::Vector2f newPos = GetPosition();

	sf::Vector2f toMove = velocity * frameSeconds;
	float squareDistToMove = VectorHelper::SquareMagnitude(toMove);

	sf::Vector2f toTarget = (*targetPoint - newPos);
	float squareDistToTarget = VectorHelper::SquareMagnitude(toTarget);

	if (squareDistToMove >= squareDistToTarget)
	{
		// We arrived!
		newPos = *targetPoint;
		if (targetPoint == &POS1)
			targetPoint = &POS2;
		else
			targetPoint = &POS1;

		// Update velocity
		sf::Vector2f vectorToNewTarget = *targetPoint - newPos;
	}
	else
	{
	}

	newPos += toMove;
}
