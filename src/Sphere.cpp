#include "Sphere.hpp"

namespace Scene
{

Sphere::Sphere(const Point& center, const double radius, uint8_t rgbaColor[Graphics::kBytesPerPixel]) : 
        center_(center), radius_(radius) 
{
    memcpy(rgbaColor_, rgbaColor, Graphics::kBytesPerPixel);
}

bool Sphere::isInside(const Point& point) const
{
    return getDistance3D(center_, point) <= radius_;
}


} // Scene