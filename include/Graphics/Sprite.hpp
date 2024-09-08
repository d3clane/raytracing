#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicsWindow.hpp"

namespace Graphics
{

class Texture;

class Sprite
{
    sf::Sprite sprite_;

public:

    void setTexture(const Texture& texture);

    friend void Window::drawSprite(const Sprite& sprite);
};


} // namespace Graphics

#endif // SPRITE_HPP