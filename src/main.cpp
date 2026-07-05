#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "imgui.h"
#include "imconfig-SFML.h"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"
#include "GameWorld.hpp"

int main()
{

    sf::VideoMode fullScreen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullScreen, "AlianWorlds", sf::Style::Fullscreen);
    sf::Clock deltaClock;

    ResourceManager::loadResources();

    Renderer renderer(window);
    SceneManager sceneManager;
    InputManager inputManager;
    AudioManager audioManager;

    window.setVerticalSyncEnabled(true);

    sceneManager.setScene(std::make_unique<GameScene>());

    while (window.isOpen())
    {
        float dt = deltaClock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ImGui::SFML::ProcessEvent(event);
            inputManager.handleEvent(event);
            sceneManager.handleEvent(event);
        }

        inputManager.update();
        sceneManager.update(inputManager, audioManager, dt);
        audioManager.update();
        ImGui::SFML::Update(window, deltaClock.restart());
        
        renderer.beginFrame();

        sceneManager.render(renderer);

        renderer.endFrame();
    }

    ImGui::SFML::Shutdown();

    return 0;
}