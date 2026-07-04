#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void handleEvent(const sf::Event &event) = 0;
    virtual void render(Renderer &render) = 0;
    virtual void update(InputManager &input, AudioManager &audioManager, float dt) = 0;
};