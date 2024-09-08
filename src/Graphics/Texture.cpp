#include "Texture.hpp"

namespace Graphics
{

Texture::Texture(unsigned int width, unsigned int height)
{
    texture_.create(width, height);
}

void Texture::loadFromFile(const std::string& filename)
{
    texture_.loadFromFile(filename);
}

} // namespace Graphics