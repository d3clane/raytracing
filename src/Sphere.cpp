#include "Sphere.hpp"

namespace Scene
{

Sphere::Sphere(const Point& center, const double radius, const Graphics::Color& color) :
    center_(center), radius_(radius), color_(color)
{
}


bool Sphere::isInside(const Point& point) const
{
    return getDistance3D(center_, point) <= radius_;
}

double Sphere::calcZ(const Graphics::WindowPoint& windowPoint, const CoordsSystem& coordsSystem) const
{
    Point coordsSystemPoint = coordsSystem.getPosInCoordsSystem(windowPoint);
    
    return calcZ(coordsSystemPoint.x, coordsSystemPoint.y);
}

double Sphere::calcZ(const double x, const double y) const 
{
    double dx = x - center_.x;
    double dy = y - center_.y;

    double squareZ = radius_ * radius_ - dx * dx - dy * dy;

    if (squareZ < 0) 
        return NAN;

    return sqrt(squareZ);
}


} // Scene