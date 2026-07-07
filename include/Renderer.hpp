#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "Light.hpp"
#include "Object.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

class Renderer
{
private:
    sf::View mainView;
public:
    Renderer(sf::RenderWindow &window)
        : window(window)
    {
        ImGui::SFML::Init(window);
        sf::Vector2u size = window.getSize();
        geometryTexture.create(size.x, size.y);
        lightTexture.create(size.x, size.y);
        setAmbientLight(0.0);
    }

    void setView(sf::View &newView)
    {
        mainView = newView;
    }

    void setAmbientLight(float value)
    {
        // Clamp the value between 0 and 1
        ambientLight = std::max(0.0f, std::min(1.0f, value));
    }

    void beginFrame()
    {
        items.clear();
        lights.clear();
        geometryTexture.clear(defaultColor);
        sf::Uint8 ambientValue = static_cast<sf::Uint8>(ambientLight * 255);
        lightTexture.clear(sf::Color(ambientValue, ambientValue, ambientValue));
        window.clear();
    }

    void submit(const sf::Drawable &drawable)
    {
        items.push_back(&drawable);
    }

    void submit(const Light &light)
    {
        lights.push_back(&light);
    }

    void submit(const Object &object)
    {
        items.push_back(object.getSprite());
        lights.push_back(&object.light);
    }

    void endFrame()
    {
        sf::Vector2u windowSize = window.getSize();

        geometryTexture.setView(mainView);

        for (const sf::Drawable *d : items)
            geometryTexture.draw(*d);
        geometryTexture.display();

        sf::RectangleShape lightQuad(sf::Vector2f(windowSize.x, windowSize.y));
        for (const Light *light : lights)
        {
            renderLightToMap(light, lightQuad, windowSize);
        }
        lightTexture.display();

        sf::Sprite geometrySprite(geometryTexture.getTexture());
        sf::Sprite lightmapSprite(lightTexture.getTexture());

        // Draw the environment normally
        window.draw(geometrySprite);

        // Draw the lightmap on top using Multiply blending
        sf::RenderStates blendMultiply(sf::BlendMultiply);
        window.draw(lightmapSprite, blendMultiply);

        ImGui::SFML::Render(window);

        window.display();
    }

private:
    void renderLightToMap(const Light *light, sf::RectangleShape &renderQuad, sf::Vector2u windowSize)
    {
        sf::Glsl::Vec3 glslColor(
            light->color.r / 255.f,
            light->color.g / 255.f,
            light->color.b / 255.f);

        ResourceManager::getResource(ShaderID::light).setUniform("u_lightPos", light->position);
        ResourceManager::getResource(ShaderID::light).setUniform("u_lightColor", glslColor);
        ResourceManager::getResource(ShaderID::light).setUniform("u_lightRadius", light->radius * light->intensity);
        ResourceManager::getResource(ShaderID::light).setUniform("u_resolution", sf::Vector2f(windowSize.x, windowSize.y));

        // CRITICAL: Use BlendAdd so overlapping light sources brighten up together
        sf::RenderStates blendAdd(sf::BlendAdd);
        blendAdd.shader = &ResourceManager::getResource(ShaderID::light);

        lightTexture.draw(renderQuad, blendAdd);
    }

    sf::RenderWindow &window;

    sf::RenderTexture geometryTexture;
    sf::RenderTexture lightTexture;

    sf::Color defaultColor = sf::Color(44, 105, 219);
    // sf::Color defaultColor = sf::Color(0, 0, 0);
    
    std::vector<const sf::Drawable *> items;
    std::vector<const Light *> lights;

    float ambientLight = 0.0f;
};