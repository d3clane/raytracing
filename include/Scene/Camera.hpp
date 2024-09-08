#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Scene/CoordsSystem.hpp"

namespace Scene
{

class Camera
{
    Point pos_;

public:
    Camera(const Point& pos) : pos_(pos) {}

    inline Point pos() const { return pos_; }
    
    void drawPixels(Graphics::Window& window, const CoordsSystem& coordsSystem, 
                    const Graphics::PixelsArray& pixelsArray) const;
};

} // Scene

#endif // CAMERA_HPP