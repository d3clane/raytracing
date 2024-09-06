#include "PixelsArray.hpp"

namespace Graphics
{

static const size_t kBytesPerPixel = 4;

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