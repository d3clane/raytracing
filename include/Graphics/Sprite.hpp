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

    void setTexture (const Texture& texture);
    void setPosition(const WindowPoint& position);
    void scale      (const float scaleX, const float scaleY);

    WindowVector getScaleInPixels() const;

    friend void Window::drawSprite(const Sprite& sprite);
};


} // namespace Graphics

#endif // SPRITE_HPP