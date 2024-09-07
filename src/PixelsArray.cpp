#include "PixelsArray.hpp"

namespace Graphics
{

namespace 
{
unsigned int getPixelPos(unsigned int x, unsigned int y, unsigned int width);

unsigned int getPixelPos(unsigned int x, unsigned int y, unsigned int width)
{
    return (y * width + x) * kBytesPerPixel;
}

uint8_t addColors(uint8_t col1, uint8_t col2, uint8_t maxColorValue)
{
    const uint16_t sumColors = (uint16_t)col1 + (uint16_t)col2;
    return sumColors > (uint16_t)maxColorValue ? maxColorValue : sumColors;
}

uint8_t mulColor(uint8_t col, double coeff, uint8_t maxColorValue)
{
    double val = col * coeff;

    return val > maxColorValue ? maxColorValue : val;
}

} // Anonymous namespace

Color Color::operator + (const Color& other) const
{
    return Color(addColors(red  (),  other.red  (), maxColorValue_), 
                 addColors(green(),  other.green(), maxColorValue_),
                 addColors(blue (),  other.blue (), maxColorValue_), 
                 std::max (alpha(),  other.alpha()));

}
Color Color::operator * (const double& coeff) const
{
    return Color(mulColor(red  (), coeff, maxColorValue_),
                 mulColor(green(), coeff, maxColorValue_),
                 mulColor(blue (), coeff, maxColorValue_),
                 alpha());
}

PixelsArray::PixelsArray(unsigned int width, unsigned int height) : 
    width_(width), height_(height), pixels_(new sf::Uint8[width * height * kBytesPerPixel]{0})
{
    for (unsigned int y = 0; y < height_; ++y)
    {
        for (unsigned int x = 0; x < width_; ++x)
        {
            pixels_[getPixelPos(x, y, width_) + 0] = 0;
            pixels_[getPixelPos(x, y, width_) + 1] = 0;
            pixels_[getPixelPos(x, y, width_) + 2] = 0;
            pixels_[getPixelPos(x, y, width_) + 3] = 255;
        }
    }
}

PixelsArray::PixelsArray(const PixelsArray& pixels) : PixelsArray::PixelsArray(pixels.width_, pixels.height_)
{
    memcpy(pixels_, pixels.pixels_, width_ * height_ * kBytesPerPixel);
}

PixelsArray::~PixelsArray()
{
    delete[] pixels_;
}

PixelsArray& PixelsArray::operator =(PixelsArray& pixels)
{
    if (this == &pixels) return pixels;

    delete[] pixels_;

    width_  = pixels.width_;
    height_ = pixels.height_;
    memcpy(pixels_, pixels.pixels_, width_ * height_ * kBytesPerPixel);

    return *this;
}

void PixelsArray::setPixel(unsigned int x, unsigned int y, const Color& color)
{
    assert(x < width_ && y < height_);

    size_t pixelPos = getPixelPos(x, y, width_);

    pixels_[pixelPos + 0] = color.red();
    pixels_[pixelPos + 1] = color.green();
    pixels_[pixelPos + 2] = color.blue();
    pixels_[pixelPos + 3] = color.alpha();
}

Color PixelsArray::getPixel(unsigned int x, unsigned int y) const
{
    assert(x < width_ && y < height_);

    size_t pixelPos = getPixelPos(x, y, width_);

    return Color(pixels_[pixelPos + 0], pixels_[pixelPos + 1], pixels_[pixelPos + 2], pixels_[pixelPos + 3]);
}

/*
const PixelsArray& PixelsArray::operator =(const PixelsArray& pixels)
{
    if (this == &pixels) return pixels;

    delete[] pixels_;

    width_  = pixels.width_;
    height_ = pixels.height_;
    pixels_ = new sf::Uint8[width_ * height_ * kBytesPerPixel];
    memcpy(pixels_, pixels.pixels_, width_ * height_ * kBytesPerPixel);
}
*/

} // Graphics 