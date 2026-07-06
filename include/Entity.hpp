#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"

#define Gravity 9.8
#define Multiplier 100

class Entity : public Object
{
private:
    sf::Vector2f m_velocity = {0, 0};

public:
    Entity()
    {
    }

    ~Entity() = default;

    virtual void onUpdate(float dt) = 0;

    void update(float dt) override
    {
        m_velocity.y += Gravity * Multiplier * dt;

        sf::Vector2f position = getPosition();
        position += m_velocity * dt;
        setPosition(position);

        onUpdate(dt);
    }
};