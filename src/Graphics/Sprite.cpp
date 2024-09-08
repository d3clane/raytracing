#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"

namespace Graphics
{

void Sprite::setTexture(const Texture& texture)
{
    sprite_.setTexture(texture.texture_);
}

} // namespace Graphics