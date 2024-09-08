#include "Graphics/Texture.hpp"

namespace Graphics
{

Texture::Texture(unsigned int width, unsigned int height)
{
    texture_.create(width, height);
}

bool Texture::loadFromFile(const std::string& filename)
{
    return texture_.loadFromFile(filename);
}

} // namespace Graphics