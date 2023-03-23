#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;

sf::Texture& AssetManager::RequestTexture(std::string assetName)
{
    std::string fullAsset = "Assets/Graphics/" + assetName + ".png";
    auto pairFound = textures.find(fullAsset);

    if (pairFound != textures.end())
    {
        // We found a texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::Texture& newTexture = textures[fullAsset];
        newTexture.loadFromFile(fullAsset);
        return newTexture;
    }
}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
    std::string fullAsset = "Assets/Fonts/" + assetName + ".ttf";
    auto pairFound = fonts.find(fullAsset);

    if (pairFound != fonts.end())
    {
        // We found a font! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::Font& newFont = fonts[fullAsset];
        newFont.loadFromFile(fullAsset);
        return newFont;
    }
}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string assetName)
{
    std::string fullAsset = "Assets/Audio/" + assetName;
    auto pairFound = soundBuffers.find(fullAsset);

    if (pairFound != soundBuffers.end())
    {
        // We found a sound buffer! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::SoundBuffer& newSoundBuffer = soundBuffers[fullAsset];
        newSoundBuffer.loadFromFile(fullAsset);
        return newSoundBuffer;
    }
}

void AssetManager::DestroyAllAssets()
{
    textures.clear();
}
