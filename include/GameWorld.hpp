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
    sf::Sprite sprt;
    Light light;

public:
    GameScene() 
        : light({100, 100}, sf::Color::White, 30.f)
    {
        sprt.setTexture(ResourceManager::getResource(TextureID::defaultTex));
        sprt.setPosition(100, 100);
        light.intensity = 10.f;
    }

    void handleEvent(const sf::Event &event) override {}
    void update(InputManager &inputManager, AudioManager &audioManager, float dt) override
    {
        float speed = 200.f;

        if (inputManager.isHeld(Action::MoveUp))
            light.position.y += -speed * dt;
        else if (inputManager.isHeld(Action::MoveDown))
            light.position.y += speed * dt;

        if (inputManager.isHeld(Action::MoveRight))
            light.position.x += speed * dt;
        else if (inputManager.isHeld(Action::MoveLeft))
            light.position.x += -speed * dt;

        if (inputManager.isPressed(Action::Interact))
            audioManager.playSoundEffect(ResourceManager::getResource(SoundID::OpenUI), {100, 100});        

        audioManager.setListenerPosition(light.position);
    }
    void render(Renderer &renderer) override
    {
        renderer.submit(sprt);
        renderer.submit(light);
    }

    void renderGUI() override
    {
        ImGui::Begin("Window title"
            //,
            // nullptr,
            // ImGuiWindowFlags_NoMove |
            // ImGuiWindowFlags_NoResize |
            // ImGuiWindowFlags_NoCollapse
        );
        ImGui::Text("Window Text");
        if (ImGui::Button("click me1!"))
        {
            std::cout << "Clicked1" << std::endl;
        }
        if (ImGui::Button("click me2!"))
        {
            std::cout << "Clicked2" << std::endl;
        }
        ImGui::End();
    }
};