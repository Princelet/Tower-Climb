#pragma once
#include <SFML/Graphics.hpp>

class SpriteObject
{
public:
	SpriteObject();
	~SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	bool CheckCollision(SpriteObject other);
	void SetColliding(bool newColliding);
	
protected:
	sf::Sprite sprite;

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

private:
	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();

	sf::Vector2f position;
	bool colliding;
};

