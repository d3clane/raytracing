#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "CoordsSystem.hpp"
#include "PixelsArray.hpp"

namespace Scene
{

class Sphere
{
    Point center_;
    double radius_;

    uint8_t rgbaColor_[Graphics::kBytesPerPixel];

public:
    Sphere(const Point& center, const double radius, uint8_t rgbaColor[Graphics::kBytesPerPixel]);

    bool isInside(const Point& point) const;

    inline double radius() const { return radius_; }
    inline const uint8_t* rgbaColor() const { return rgbaColor_; }

    inline const double getZ(const double x, const double y) const 
    {
        double dx = x - center_.x;
        double dy = y - center_.y;

        double squareZ = radius_ * radius_ - dx * dx - dy * dy;

        if (squareZ < 0) return NAN;
        return sqrt(squareZ);
    }
};

} // Scene


#endif // SPHERE_HPP