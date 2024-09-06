#ifndef PIXELS_ARRAY_HPP
#define PIXELS_ARRAY_HPP

#include <SFML/Graphics.hpp>
#include "GraphicsWindow.hpp"

namespace Graphics
{

static const size_t kBytesPerPixel = 4;

class PixelsArray
{
private:
    sf::Uint8* pixels_;
    unsigned int width_, height_;

public:
    PixelsArray(unsigned int width, unsigned int height);
    PixelsArray(const PixelsArray& pixels);
    ~PixelsArray();

    PixelsArray& operator =(PixelsArray& pixels);
    //const PixelsArray& operator =(const PixelsArray& pixels);

    void setPixel(unsigned int x, unsigned int y, 
                  uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    friend void Window::drawPixels(const PixelsArray& pixels);
};

} // Graphics

#endif // PIXELS_ARRAY_HPP