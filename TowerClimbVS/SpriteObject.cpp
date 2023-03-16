#include "SpriteObject.h"
#include "VectorHelper.h"

SpriteObject::SpriteObject()
 : position(0.0f, 0.0f)
	, colliding(false)
	, collisionOffset(0.0f, 0.0f)
	, collisionScale(1.0f, 1.0f)
{
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);

	bool drawCollider = true;

	if (drawCollider)
	{
		sf::CircleShape circle;

		sf::Vector2f shapePos = GetCollisionCentre();
		float circleRadius = GetCircleColliderRadius();;
		shapePos.x -= circleRadius;
		shapePos.y-= circleRadius;

		circle.setPosition(shapePos);
		circle.setRadius(circleRadius);

		// If a collision isn't occurring, the collision circle will be green.
		sf::Color collisionColor = sf::Color::Green;
		if (colliding)
			collisionColor = sf::Color::Red;
		collisionColor.a = 100;

		circle.setFillColor(collisionColor);

		target.draw(circle);
	}
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(position);
}
void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool SpriteObject::CheckCollision(SpriteObject other)
{
	// Get the vector representing displacement between two circles
	sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

	// Get vector's magnitude: how far the centres are
	float squareDistance = VectorHelper::SquareMagnitude(displacement);

	// Combine that to the combined radii of the circles
	float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

	return squareDistance <= combinedRadii * combinedRadii;
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += collisionOffset.x + bounds.width * 0.5f;
	centre.y += collisionOffset.y + bounds.height * 0.5f;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
		return bounds.width * 0.5f;
	else
		return bounds.height * 0.5f;
}
