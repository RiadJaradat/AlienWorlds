#pragma once

#include <SFML/Graphics.hpp>

class Object
{
private:
    sf::RectangleShape bounds;
    sf::Sprite sprt;
    sf::Texture *texture = nullptr;

public:
    virtual void update(float dt) = 0;

    Object()
    { 
        sprt.setPosition(bounds.getPosition());
        sprt.setOrigin(bounds.getOrigin());
    }

    ~Object() = default;

    sf::FloatRect getBounds() const
    {
        return bounds.getGlobalBounds();
    }

    const sf::Sprite *getSprite() const 
    {
        return &sprt;
    }

    sf::Vector2f getPosition() const 
    {
        if (bounds.getPosition() != sprt.getPosition())
            throw std::logic_error("Bad Positioning");

        return bounds.getPosition();
    }

    void setPosition(sf::Vector2f newPos)
    {

        bounds.setPosition(newPos);
        sprt.setPosition(newPos);
    }

    void setOrigin(sf::Vector2f newOrigin)
    {
        bounds.setOrigin(newOrigin);
        sprt.setOrigin(newOrigin);
    }

    void setTexture(sf::Texture &texture)
    {
        this->texture = &texture;
        sprt.setTexture(*this->texture);
    }

    bool intersects(const Object &other) const
    {
        return getBounds().intersects(other.getBounds());
    }
};