#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Graphics/PixelsArray.hpp"

#include "Scene/CoordsSystem.hpp"

namespace Scene
{

class Sphere
{
    Point center_;
    double radius_;
    Graphics::Color color_;
public:
    Sphere(const Point& center, const double radius, const Graphics::Color& color);

    bool isInside(const Point& point) const;

    Point center() const { return center_; }
    Graphics::Color color() const { return color_; }
    
    double calcZ(const Graphics::WindowPoint& windowPoint, const CoordsSystem& coordsSystem) const;
    double calcZ(const double x, const double y) const; 
};

} // Scene


#endif // SPHERE_HPP