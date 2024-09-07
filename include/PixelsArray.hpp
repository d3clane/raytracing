#ifndef PIXELS_ARRAY_HPP
#define PIXELS_ARRAY_HPP

#include <SFML/Graphics.hpp>
#include "GraphicsWindow.hpp"

namespace Graphics
{

static const size_t kBytesPerPixel = 4;

struct Color
{
private:
    enum class ColorId
    {
        RED,
        GREEN,
        BLUE,
        ALPHA,
    };

    const uint8_t maxColorValue_ = 255;
public:
    uint8_t rgbaColors[kBytesPerPixel];

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        rgbaColors[(int)ColorId::RED]   = red;
        rgbaColors[(int)ColorId::GREEN] = green;
        rgbaColors[(int)ColorId::BLUE]  = blue;
        rgbaColors[(int)ColorId::ALPHA] = alpha;
    }

    inline uint8_t red()   const { return rgbaColors[(int)ColorId::RED   ]; }
    inline uint8_t green() const { return rgbaColors[(int)ColorId::GREEN ]; }
    inline uint8_t blue()  const { return rgbaColors[(int)ColorId::BLUE  ]; }
    inline uint8_t alpha() const { return rgbaColors[(int)ColorId::ALPHA ]; }

    Color operator + (const Color& other) const;
    Color operator * (const double& coeff) const;
};

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
    //const PixelsArray& operator =(const PixelsArray& pixels)

    void  setPixel(unsigned int x, unsigned int y, const Color& color);
    Color getPixel(unsigned int x, unsigned int y) const;

    inline unsigned int width()  const { return width_;  }
    inline unsigned int height() const { return height_; }

    friend void Window::drawPixels(const PixelsArray& pixels);
};

} // Graphics

#endif // PIXELS_ARRAY_HPP