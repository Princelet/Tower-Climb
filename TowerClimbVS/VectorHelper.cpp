#include "VectorHelper.h"

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrt(SquareMagnitude(vec));
}

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}