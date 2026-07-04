#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>

#include "Scene.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"
#include "Renderer.hpp"

class SceneManager
{
private:
    std::unique_ptr<Scene> currentScene;

public:
    void setScene(std::unique_ptr<Scene> &&newScene) { currentScene = std::move(newScene); };
    void handleEvent(const sf::Event &event)
    {
        assert(currentScene);
        currentScene->handleEvent(event);
    }
    void update(InputManager &input, AudioManager &audioManager, float dt)
    {
        assert(currentScene);
        currentScene->update(input, audioManager, dt);
    }
    void render(Renderer &target)
    {
        assert(currentScene);
        currentScene->render(target);
    }
};