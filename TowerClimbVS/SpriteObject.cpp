#include "SpriteObject.h"
#include "VectorHelper.h"
#include <algorithm>

SpriteObject::SpriteObject()
 : position(0.0f, 0.0f)
	, colliding(false)
	, collisionOffset(0.0f, 0.0f)
	, collisionScale(1.0f, 1.0f)
	, collisionType(CollisionType::AABB)
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

	// If a collision isn't occurring, the collision circle will be green.
	sf::Color collisionColor = sf::Color::Green;
	if (colliding)
		collisionColor = sf::Color::Red;
	collisionColor.a = 100;

	if (drawCollider)
	{
		switch (collisionType)
		{
		case CollisionType::CIRCLE:
			{
			sf::CircleShape circle;

			sf::Vector2f shapePos = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();;
			shapePos.x -= circleRadius;
			shapePos.y -= circleRadius;

			circle.setPosition(shapePos);
			circle.setRadius(circleRadius);

			circle.setFillColor(collisionColor);

			target.draw(circle);
			break;
			}
		case CollisionType::AABB:
			{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
			rectangle.setFillColor(collisionColor);

			target.draw(rectangle);
			break;
			}
		default:
			break;
		}
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
	switch (collisionType)
	{
	case CollisionType::CIRCLE:
		{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			// Get the vector representing displacement between two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			// Get vector's magnitude: how far the centres are
			float squareDistance = VectorHelper::SquareMagnitude(displacement);

			// Combine that to the combined radii of the circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			return squareDistance <= combinedRadii * combinedRadii;
		}
		else
			// Use function to check if the collisions are different. Boolean is set to True if the first object is a circle, and False ifit is a rectangle
			return CheckDifferentCollision(other, true);
		}
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
			return GetAABB().intersects(other.GetAABB());
		else
			return CheckDifferentCollision(other, false);
	}
	default:
		return false;
	}
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

bool SpriteObject::CheckDifferentCollision(SpriteObject other, bool isCircle)
{
	// Handles a circle colliding with a rectangle

	SpriteObject* objectA;
	SpriteObject* objectB;

	if (isCircle)
	{
		objectA = this;
		objectB = &other;
	}
	else
	{
		objectA = &other;
		objectB = this;
	}

	sf::Vector2f nearestPointToCircle = objectA->GetCollisionCentre(); // Actual circle centre to start with
	sf::FloatRect otherAABB = objectB->GetAABB();
	// Clamp the circle centre to the AABB of the other object
	nearestPointToCircle.x = fmaxf(otherAABB.left, fminf(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
	nearestPointToCircle.y = fmaxf(otherAABB.top, fminf(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

	// Get the vector representing displacement between two circles
	sf::Vector2f displacement = nearestPointToCircle - objectA->GetCollisionCentre();

	// Get vector's magnitude: how far the centres are
	float squareDistance = VectorHelper::SquareMagnitude(displacement);

	float circleRadius = objectA->GetCircleColliderRadius();

	return squareDistance <= circleRadius * circleRadius;
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
		minDistance.x = -minDistance.x;
	if (actualDistance.y < 0)
		minDistance.y = -minDistance.y;

	return actualDistance - minDistance;
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

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}
