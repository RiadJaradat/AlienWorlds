#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

/*
//////////////////// Joystick Manual ///////////////////
// Axis R: R2            * default: -100, max 100, min -100
// Axis Z: L2            * default: -100, max 100, min -100
// Axis V: R3 y position * default:  000, max 100, min -100
// Axis U: R3 x position * default:  000, max 100, min -100
// Axis X: L3 x position * default:  000, max 100, min -100
// Axis Y: L3 y position * default:  000, max 100, min -100
//
// Button ID 0: button x
// Button ID 1: button o
// Button ID 2: button [] (square)
// Button ID 3: button /\ (triangle)
// Button ID 4: button L1
// Button ID 5: button R1
// Button ID 6: button share
// Button ID 7: button option
// Button ID 8: button home
// Button ID 9: button L3
// Button ID 10: button R3
*/

enum class Action
{
    MoveUp,
    MoveDown,
    MoveRight,
    MoveLeft,
    Interact
};

struct ActionState
{
    bool held = false;
    bool pressed = false;
};

class InputManager
{
private:
    std::unordered_map<Action, ActionState> state;

    void updateAction(Action action, bool isCurrentlyHardwareActive)
    {
        state[action].pressed = (isCurrentlyHardwareActive && !state[action].held);
        state[action].held = isCurrentlyHardwareActive;
    }

public:
    bool JoyStick = false;

    const float deadzone = 20.f;
    const int JoystickID = 0;

    void update()
    {
        JoyStick = sf::Joystick::isConnected(0);

        if (!JoyStick)
        {
            updateAction(Action::MoveDown, sf::Keyboard::isKeyPressed(sf::Keyboard::S));
            updateAction(Action::MoveUp, sf::Keyboard::isKeyPressed(sf::Keyboard::W));
            updateAction(Action::MoveRight, sf::Keyboard::isKeyPressed(sf::Keyboard::D));
            updateAction(Action::MoveLeft, sf::Keyboard::isKeyPressed(sf::Keyboard::A));
            
            updateAction(Action::Interact,  sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }
        else
        {
            float x = sf::Joystick::getAxisPosition(JoystickID, sf::Joystick::Axis::X);
            float y = sf::Joystick::getAxisPosition(JoystickID, sf::Joystick::Axis::Y);

            updateAction(Action::MoveRight, (x > deadzone));
            updateAction(Action::MoveLeft, (x < -deadzone));
            updateAction(Action::MoveUp, (y < -deadzone));
            updateAction(Action::MoveDown, (y > deadzone));

            updateAction(Action::Interact, sf::Joystick::isButtonPressed(JoystickID, 0));
        }
    }

    void handleEvent(sf::Event &event)
    {
        // later code to handle events such as mouse scroll
    }

    bool isHeld(Action a)
    {
        return state[a].held;
    }

    bool isPressed(Action a)
    {
        return state[a].pressed;
    }
};