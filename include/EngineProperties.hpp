#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct EP
{
    
    const static inline std::string assetsFolder = "../assets/";
    const static inline std::string WindowTitle = "AlienWorlds";
    const static inline sf::Vector2i tileSize = sf::Vector2i(64, 64);
    
    const static inline sf::VideoMode fullScreen = sf::VideoMode::getDesktopMode();
    
    static inline bool VSyncEnable = true;
};
