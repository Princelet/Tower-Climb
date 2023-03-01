#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
	static sf::Texture& RequestTexture(std::string textureName);

	static void DestroyAllAssets();

private:
	static std::map<std::string, sf::Texture> textures;
};

