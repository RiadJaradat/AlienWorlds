#pragma once

#include "Scene.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Light.hpp"
#include "SceneManager.hpp"
#include "EngineProperties.hpp"
#include "ShallowWaters.hpp"
#include "Player.hpp"

class GameScene : public Scene
{
private:
    ShallowWaters shallowWaters;

    Player player;

    sf::View Camera;

public:
    GameScene()
    {
        player.setPosition({shallowWaters.biomeOverlay.getGlobalBounds().width / 2, 0});
    }

    void handleEvent(const sf::Event &event) override {}
    void update(InputManager &inputManager, AudioManager &audioManager, float dt) override
    {
        
    }
    void render(Renderer &renderer) override
    {
        renderer.setView(Camera);
        renderer.setAmbientLight(shallowWaters.ambientLight);
        renderer.submit(shallowWaters.biomeOverlay);
        renderer.submit(shallowWaters.light);
        renderer.submit(player);
    }
    void renderGUI(SceneManager &sceneManager) override {}
};