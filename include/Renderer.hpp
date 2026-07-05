#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "Light.hpp"
#include "ResourceManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

class Renderer
{
public:
    Renderer(sf::RenderWindow &window)
        : window(window)
    {
        ImGui::SFML::Init(window);
        sf::Vector2u size = window.getSize();
        geometryTexture.create(size.x, size.y);
        lightTexture.create(size.x, size.y);
    }

    void beginFrame()
    {
        items.clear();
        lights.clear();
        geometryTexture.clear(sf::Color(0, 0, 50)); 
        lightTexture.clear(sf::Color(0, 0, 0)); 
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

    void endFrame()
    {
        sf::Vector2u windowSize = window.getSize();

        for (const sf::Drawable *d : items)
            geometryTexture.draw(*d);
        geometryTexture.display();

        sf::RectangleShape lightQuad(sf::Vector2f(windowSize.x, windowSize.y));
        for (const Light* light : lights)
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
    void renderLightToMap(const Light* light, sf::RectangleShape& renderQuad, sf::Vector2u windowSize)
    {
        sf::Glsl::Vec3 glslColor(
            light->color.r / 255.f, 
            light->color.g / 255.f, 
            light->color.b / 255.f
        );

        ResourceManager::lightShader.setUniform("u_lightPos", light->position);
        ResourceManager::lightShader.setUniform("u_lightColor", glslColor);
        ResourceManager::lightShader.setUniform("u_lightRadius", light->radius * light->intensity);
        ResourceManager::lightShader.setUniform("u_resolution", sf::Vector2f(windowSize.x, windowSize.y));

        // CRITICAL: Use BlendAdd so overlapping light sources brighten up together
        sf::RenderStates blendAdd(sf::BlendAdd);
        blendAdd.shader = &ResourceManager::lightShader;

        lightTexture.draw(renderQuad, blendAdd);
    }

    sf::RenderWindow &window;

    sf::RenderTexture geometryTexture;
    sf::RenderTexture lightTexture;

    std::vector<const sf::Drawable *> items;
    std::vector<const Light*> lights;
};