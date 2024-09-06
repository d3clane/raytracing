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
} // Anonymous namespace

PixelsArray::PixelsArray(unsigned int width, unsigned int height) : 
    width_(width), height_(height), pixels_(new sf::Uint8[width * height * kBytesPerPixel])
{
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



void PixelsArray::setPixel(unsigned int x, unsigned int y, 
                           uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    assert(x < width_ && y < height_);

    size_t pixelPos = getPixelPos(x, y, width_);

    pixels_[pixelPos + 0] = red;
    pixels_[pixelPos + 1] = green;
    pixels_[pixelPos + 2] = blue;
    pixels_[pixelPos + 3] = alpha;
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