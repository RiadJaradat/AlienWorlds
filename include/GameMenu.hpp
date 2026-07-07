#pragma once

#include "Scene.hpp"
#include "Renderer.hpp"
#include "SceneManager.hpp"
#include "GameScene.hpp"

class GameMenu : public Scene
{
public:
    void update(InputManager &input, AudioManager &audioManager, float dt) override {}
    void render(Renderer &renderer) override
    {
        renderer.setAmbientLight(1.f);
    }
    void renderGUI(SceneManager &sceneManager) override
    {

        float buttonWidth = 200.0f;
        float buttonHeight = 40.0f;

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImVec2 center = viewport->GetCenter();

        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

        ImGui::SetNextWindowSize(ImVec2(800.0f, 500.0f), ImGuiCond_Always);

        ImGui::Begin("Alien Worlds",
                     nullptr,
                     ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove);

        float centerY = ImGui::GetWindowHeight() * 0.5f - (buttonHeight * 0.5f);
        float centerX = (ImGui::GetWindowWidth() - buttonWidth) * 0.5f;

        ImGui::SetCursorPosX(centerX);
        ImGui::SetCursorPosY(centerY - 50); // Move up slightly
        if (ImGui::Button("Play", ImVec2(buttonWidth, buttonHeight)))
            sceneManager.setScene(std::make_unique<GameScene>());

        ImGui::Spacing();

        ImGui::SetCursorPosX(centerX);
        if (ImGui::Button("Quit", ImVec2(buttonWidth, buttonHeight)))
            exit(0);

        ImGui::End();
    }
    void handleEvent(const sf::Event &event) override {}
};