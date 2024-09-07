#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "CoordsSystem.hpp"

namespace Scene
{

class Camera
{
    Point pos_;

public:
    Camera(const Point& pos) : pos_(pos) {}

    void drawPixels(Graphics::Window& window, const CoordsSystem& coordsSystem, 
                    const Graphics::PixelsArray& pixelsArray) const;
};

} // Scene

#endif // CAMERA_HPP