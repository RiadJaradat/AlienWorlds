#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "imgui.h"
#include "imconfig-SFML.h"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "inputManager.hpp"
#include "AudioManager.hpp"
#include "GameWorld.hpp"

struct EngineProperties
{
    static inline const std::string WindowTitle = "AlienWorlds";
    static inline bool VSyncEnable = true;
};

class Engine
{
private:
    sf::VideoMode fullScreen = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window;
    sf::Clock deltaClock;

    Renderer renderer;
    SceneManager sceneManager;
    InputManager inputManager;
    AudioManager audioManager;

    void HandleEvents(sf::Event &event)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            ImGui::SFML::ProcessEvent(event);
            inputManager.handleEvent(event);
            sceneManager.handleEvent(event);
        }
    }

    void update(float dt)
    {
        inputManager.update();
        sceneManager.update(inputManager, audioManager, dt);
        audioManager.update();
        ImGui::SFML::Update(window, deltaClock.restart());
    }

    void render()
    {
        renderer.beginFrame();

        sceneManager.render(renderer);

        renderer.endFrame();
    }

public:
    Engine() : window(fullScreen, EngineProperties::WindowTitle, sf::Style::Fullscreen),
               renderer(window)
    {
        window.setVerticalSyncEnabled(true);

        sceneManager.setScene(std::make_unique<GameScene>());
    }

    ~Engine()
    {
        ImGui::SFML::Shutdown();
        exit(0);
    }

    void run()
    {
        while (window.isOpen())
        {
            float dt = deltaClock.restart().asSeconds();

            sf::Event event;

            HandleEvents(event);

            update(dt);

            render();
        }
    }
};