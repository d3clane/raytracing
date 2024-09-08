#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SFML/Graphics.hpp>

#include "Graphics/Sprite.hpp"

namespace Graphics
{

class Texture
{
    sf::Texture texture_;

public:
    Texture(unsigned int width, unsigned int height);

    void loadFromFile(const std::string& filename);

    friend void Sprite::setTexture(const Texture& texture);
};

} // namespace Graphics

#endif // TEXTURE_HPP