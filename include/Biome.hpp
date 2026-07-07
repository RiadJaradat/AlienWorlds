#pragma once

#include <SFML/Graphics.hpp>

#include "Light.hpp"
#include "EngineProperties.hpp"

class Biome
{
public:
    sf::RectangleShape biomeOverlay;
    Light light;
    float ambientLight = 1.f;

    Biome()
    {
        biomeOverlay.setPosition(0, 0);
    }
};