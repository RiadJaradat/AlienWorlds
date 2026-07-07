#pragma once

#include "Entity.hpp"
#include "inputManager.hpp"

class Player : public Entity
{
public:

    Player()
    {
        light.color = sf::Color::Yellow;
        light.intensity = 10;
        light.radius = 100;
    }

    void onUpdate(InputManager &inputManager, AudioManager &audioManager, float dt) override
    {
        sf::Vector2i direction = {0, 0};

        float speed = 150.f;

        if (inputManager.isHeld(Action::MoveUp))
            direction.y = -1;
        else if (inputManager.isHeld(Action::MoveDown))
            direction.y = 1;

        if (inputManager.isHeld(Action::MoveRight))
            direction.x = 1;
        else if (inputManager.isHeld(Action::MoveLeft))
            direction.x = -1;

        setPosition({speed * dt * direction.x, speed * dt * direction.y});
    }
};