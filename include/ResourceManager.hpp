#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

#define ASSETSFOLDER "../assets/"

enum class TextureID
{
    defaultTex
};
enum class ShaderID
{
    light
};
enum class SoundID
{
    OpenUI
};

class ResourceManager
{
private:
    ResourceManager() = delete;

    const static inline sf::Vector2i tileSize = sf::Vector2i(64, 64);

    static std::string getPath(TextureID T)
    {
        switch (T)
        {
        case TextureID::defaultTex:
            return ASSETSFOLDER "pngs/default.png";
        }
    }
    static std::string getPath(ShaderID S)
    {
        switch (S)
        {
        case ShaderID::light:
            return ASSETSFOLDER "shaders/light_shader.frag";
        }
    }
    static std::string getPath(SoundID S)
    {
        switch (S)
        {
        case SoundID::OpenUI:
            return ASSETSFOLDER "SoundEffects/UI.wav";
        }
    }

    static inline std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> loadedTextures;
    static inline std::unordered_map<ShaderID, std::unique_ptr<sf::Shader>> loadedshaders;
    static inline std::unordered_map<SoundID, std::unique_ptr<sf::SoundBuffer>> loadedSounds;

public:
    static sf::Texture getTile(const sf::Texture &Tileset, const sf::Vector2i &index)
    {
        sf::Texture subText;
        subText.create(tileSize.x, tileSize.y);

        subText.update(Tileset, index.x * tileSize.x, index.y * tileSize.y);

        return subText;
    }

    static sf::Texture &getResource(TextureID id)
    {
        if (loadedTextures.find(id) == loadedTextures.end())
        {
            auto text = std::make_unique<sf::Texture>();
            if (!text->loadFromFile(getPath(id)))
                std::cerr << "Failed to load texure" << std::endl;
            loadedTextures[id] = std::move(text);
        }
        return *loadedTextures[id];
    }
    static sf::Shader &getResource(ShaderID id)
    {
        if (loadedshaders.find(id) == loadedshaders.end())
        {
            auto text = std::make_unique<sf::Shader>();
            if (!text->loadFromFile(getPath(id), sf::Shader::Fragment))
                std::cerr << "Failed to load shader" << std::endl;
            loadedshaders[id] = std::move(text);
        }
        return *loadedshaders[id];
    }
    static sf::SoundBuffer &getResource(SoundID id)
    {
        if (loadedSounds.find(id) == loadedSounds.end())
        {
            auto text = std::make_unique<sf::SoundBuffer>();
            if (!text->loadFromFile(getPath(id)))
                std::cerr << "Failed to load sound" << std::endl;
            loadedSounds[id] = std::move(text);
        }
        return *loadedSounds[id];
    }
};