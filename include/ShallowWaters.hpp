#pragma once

#include <SFML/Graphics.hpp>

#include "Biome.hpp"
#include "EngineProperties.hpp"

class ShallowWaters : public Biome
{
public:

    ShallowWaters() : Biome()
    {
        biomeOverlay.setFillColor(sf::Color(42, 201, 138, 125));
        biomeOverlay.setSize({EP::fullScreen.width, EP::fullScreen.height});
        biomeOverlay.setScale(5, 5);
        light.color = sf::Color::White;
        light.position = {EP::fullScreen.width / 2, 0};
        light.intensity = 10.f;
        light.radius = 100.f;
        ambientLight = 0.8;
    }
};