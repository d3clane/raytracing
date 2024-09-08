#ifndef CONVERTERS_HPP
#define CONVERTERS_HPP

#include <SFML/Graphics.hpp>

#include "Graphics/Mouse.hpp"
#include "Graphics/Events.hpp"

namespace Graphics
{

sf::Mouse::Button convertButtonToSfButton(const Mouse::Button& button);
Mouse::Button convertSfButtonToButton(const sf::Mouse::Button& sfButton);

sf::Mouse::Wheel  convertWheelToSfWheel  (const Mouse::Wheel& wheel);

Event::KeyCode convertSfKeyCodeToKeyCode(sf::Keyboard::Key sfKeyCode);

} // namespace Graphics

#endif // CONVERTERS_HPP