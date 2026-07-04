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
};