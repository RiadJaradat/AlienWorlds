#pragma once

#include <SFML/Graphics.hpp>

class Light
{
public:
    sf::Vector2f position;
    sf::Color color;
    float radius = 100.f;
    float intensity = 1.f;

    Light(sf::Vector2f position, sf::Color color = sf::Color::White, float radius = 100.f)
        : position(position), color(color), radius(radius)
    {}
    Light() {}
};