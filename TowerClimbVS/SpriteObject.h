#pragma once
#include <SFML/Graphics.hpp>

class SpriteObject
{
public:
	SpriteObject();
	~SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

protected:
	sf::Sprite sprite;
};

