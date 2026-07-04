#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define ASSETSFOLDER "../assets/"

// ResorseManager
// ResourceManager

class ResourceManager
{
private:
    ResourceManager() = delete;

    const static inline sf::Vector2i tileSize = sf::Vector2i(64, 64);

public:

    // images:
    static inline sf::Texture defaultTexture;
    
    // shaders;
    static inline sf::Shader lightShader;

    // soud effects
    static inline sf::SoundBuffer OpenUI;

    static void loadResources()
    {
        defaultTexture.loadFromFile(ASSETSFOLDER "pngs/default.png");

        lightShader.loadFromFile(ASSETSFOLDER "shaders/light_shader.frag", sf::Shader::Fragment);
    
        OpenUI.loadFromFile(ASSETSFOLDER "SoundEffects/UI.wav");
    }

    static sf::Texture getTile(const sf::Texture &Tileset, const sf::Vector2i& index)
    {
        sf::Texture subText;
        subText.create(tileSize.x, tileSize.y);

        subText.update(Tileset, index.x * tileSize.x, index.y * tileSize.y);

        return subText;
    }
};