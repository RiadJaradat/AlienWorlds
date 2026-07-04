#pragma once

#include "Scene.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Light.hpp"

/*
comments inside if uncommented gives you a test case to test the:
        * light system
        * audio system
        * input system
        * rendering system
*/

class GameScene : public Scene
{
private:
    // sf::Sprite sprt;
    // Light light;

public:
    GameScene() 
        // : light({100, 100}, sf::Color::White, 30.f)
    {
        // sprt.setTexture(ResourceManager::defaultTexture);
        // sprt.setPosition(100, 100);
        // light.intensity = 10.f;
    }

    void handleEvent(const sf::Event &event) override {}
    void update(InputManager &inputManager, AudioManager &audioManager, float dt) override
    {
        // float speed = 200.f;

        // if (inputManager.isHeld(Action::MoveUp))
        //     light.position.y += -speed * dt;
        // else if (inputManager.isHeld(Action::MoveDown))
        //     light.position.y += speed * dt;

        // if (inputManager.isHeld(Action::MoveRight))
        //     light.position.x += speed * dt;
        // else if (inputManager.isHeld(Action::MoveLeft))
        //     light.position.x += -speed * dt;

        // if (inputManager.isPressed(Action::Interact))
        //     audioManager.playSoundEffect(ResourceManager::OpenUI, {100, 100});        

        // audioManager.setLisitenerPosition(light.position);
    }
    void render(Renderer &renderer) override
    {
        // renderer.submit(sprt);
        // renderer.submit(light);
    }
};