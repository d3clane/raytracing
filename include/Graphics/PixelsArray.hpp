#ifndef PIXELS_ARRAY_HPP
#define PIXELS_ARRAY_HPP

#include <SFML/Graphics.hpp>

#include "Graphics/GraphicsWindow.hpp"

namespace Graphics
{

static const size_t kBytesPerPixel = 4;

struct Color
{
private:
    static const uint8_t maxColorValue_ = 255;

public:
    uint8_t red_, green_, blue_, alpha_;

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
        : red_{red}, green_{green}, blue_{blue}, alpha_{alpha} {}
    Color() : Color(0, 0, 0, 255) {}
    explicit Color(const sf::Color& color) : Color(color.r, color.g, color.b, color.a) {}

    Color operator +(const Color& other)  const;
    Color operator *(const double& coeff) const;
    Color operator *(const Color& other)  const;

    explicit operator sf::Color() { return sf::Color(red_, green_, blue_, alpha_); }
};

class PixelsArray
{
private:
    sf::Uint8* pixels_;

    Graphics::WindowPoint topLeftPixelWindowPos_;
    unsigned int width_, height_;

public:
    PixelsArray(unsigned int width, unsigned int height, const Graphics::WindowPoint& topLeftPixelPos);
    PixelsArray(const PixelsArray& pixels);
    ~PixelsArray();

    PixelsArray& operator =(PixelsArray& pixels);
    //const PixelsArray& operator =(const PixelsArray& pixels)

    void  setPixel(unsigned int x, unsigned int y, const Color& color);
    Color getPixel(unsigned int x, unsigned int y) const;

    void moveImage   (Graphics::WindowVector direction);
    void moveImageByX(int dx);
    void moveImageByY(int dy);

    inline unsigned int width()  const { return width_;  }
    inline unsigned int height() const { return height_; }

    inline Graphics::WindowPoint middlePixelWindowPos() const
    {
        return topLeftPixelWindowPos_ + Graphics::WindowPoint{width_ / 2, height_ / 2};
    }

    friend void Window::drawPixels(const PixelsArray& pixels);
};

} // Graphics

#endif // PIXELS_ARRAY_HPP