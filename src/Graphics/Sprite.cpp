#include <SFML/Graphics.hpp>

#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"


namespace Graphics
{

void Sprite::setTexture(const Texture& texture)
{
    sprite_.setTexture(texture.texture_);
}

void Sprite::setPosition(const WindowPoint& position)
{
    sprite_.setPosition(position.x, position.y);
}

void Sprite::scale(const float scaleX, const float scaleY)
{
    sprite_.scale(scaleX, scaleY);
}

void Sprite::scaleInPixels(const WindowVector& scaleInPixels)
{
    WindowVector currentScale = getScaleInPixels();
    if (currentScale.x == 0 || currentScale.y == 0)
        return;

    sprite_.scale((double)scaleInPixels.x / currentScale.x, (double)scaleInPixels.y / currentScale.y);
}

WindowVector Sprite::getScaleInPixels() const
{
    const sf::Texture* texture = sprite_.getTexture();
    if (texture == nullptr)
        return WindowVector(0, 0);
 
    return WindowVector(texture->getSize().x, texture->getSize().y);
}

} // namespace Graphics