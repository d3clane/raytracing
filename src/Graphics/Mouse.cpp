#include <SFML/Graphics.hpp>

#include "Graphics/GraphicsWindow.hpp"
#include "Mouse.hpp"

namespace Graphics
{

namespace Mouse
{

namespace
{

sf::Mouse::Button convertButtonToSfButton(const Button& button)
{
    switch (button)
    {
        case Button::Left:      return sf::Mouse::Left;
        case Button::Right:     return sf::Mouse::Right;
        case Button::Middle:    return sf::Mouse::Middle;
        case Button::XButton1:  return sf::Mouse::XButton1;
        case Button::XButton2:  return sf::Mouse::XButton2;
        default:                assert(false); // unreachable 
    }

    assert(false); // unreachable
    return sf::Mouse::Left;
}

sf::Mouse::Wheel convertWheelToSfWheel(const Wheel& wheel)
{
    switch (wheel)
    {
        case Wheel::VerticalWheel: return sf::Mouse::VerticalWheel;
        case Wheel::HorizontalWheel: return sf::Mouse::HorizontalWheel;
        default: assert(false); // unreachable
    }

    assert(false); // unreachable
    return sf::Mouse::VerticalWheel;
}

} // namespace anonymous

bool isButtonPressed(const Button& button)
{
    return sf::Mouse::isButtonPressed(convertButtonToSfButton(button));
}

WindowPoint getPosition(const Window& window)
{
    sf::Vector2i sfMousePosition = sf::Mouse::getPosition(window.window_);

    return WindowPoint(sfMousePosition.x, sfMousePosition.y);
}

} // namespace Mouse

} // namespace Graphics