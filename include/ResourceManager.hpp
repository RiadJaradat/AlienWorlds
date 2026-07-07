#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <EngineError.hpp>
#include "EngineProperties.hpp"


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


    static std::string getPath(TextureID T)
    {
        switch (T)
        {
        case TextureID::defaultTex:
            return EP::EP::assetsFolder + + "pngs/default.png";
        }
    }
    static std::string getPath(ShaderID S)
    {
        switch (S)
        {
        case ShaderID::light:
            return EP::assetsFolder + "shaders/light_shader.frag";
        }
    }
    static std::string getPath(SoundID S)
    {
        switch (S)
        {
        case SoundID::OpenUI:
            return EP::assetsFolder + "SoundEffects/UI.wav";
        }
    }

    static inline std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> loadedTextures;
    static inline std::unordered_map<ShaderID, std::unique_ptr<sf::Shader>> loadedShaders;
    static inline std::unordered_map<SoundID, std::unique_ptr<sf::SoundBuffer>> loadedSounds;

public:
    static sf::Texture getTile(const sf::Texture &Tileset, const sf::Vector2i &index)
    {
        sf::Texture subText;
        subText.create(EP::tileSize.x, EP::tileSize.y);

        subText.update(Tileset, index.x * EP::tileSize.x, index.y * EP::tileSize.y);

        return subText;
    }

    static sf::Texture &getResource(TextureID id)
    {
        if (loadedTextures.find(id) == loadedTextures.end())
        {
            auto text = std::make_unique<sf::Texture>();
            if (!text->loadFromFile(getPath(id)))
                throw EngineError("Failed to load texture");
            loadedTextures[id] = std::move(text);
        }
        return *loadedTextures[id];
    }
    static sf::Shader &getResource(ShaderID id)
    {
        if (loadedShaders.find(id) == loadedShaders.end())
        {
            auto text = std::make_unique<sf::Shader>();
            if (!text->loadFromFile(getPath(id), sf::Shader::Fragment))
                throw EngineError("Failed to load shader");
            loadedShaders[id] = std::move(text);
        }
        return *loadedShaders[id];
    }
    static sf::SoundBuffer &getResource(SoundID id)
    {
        if (loadedSounds.find(id) == loadedSounds.end())
        {
            auto text = std::make_unique<sf::SoundBuffer>();
            if (!text->loadFromFile(getPath(id)))
                throw EngineError("Failed to load sound");
            loadedSounds[id] = std::move(text);
        }
        return *loadedSounds[id];
    }
};