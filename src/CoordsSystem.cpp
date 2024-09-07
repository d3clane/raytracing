#include <iostream>

#include "CoordsSystem.hpp"
#include "PixelsArray.hpp"
#include "Sphere.hpp"

namespace Scene
{

namespace 
{

void changeOneArgScale(int& step, const int delta);

void changeOneArgScale(int& step, const int delta)
{
    if (delta < 0 && step <= -delta) step = 1;
    else step += delta;
}

} // anonymous namespace

using Graphics::WindowLine;

void CoordsSystem::moveCenter (const Graphics::WindowPoint& delta)
{
    center_.x += delta.x;
    center_.y += delta.y;
}

void CoordsSystem::changeScale(const int delta)
{
    changeOneArgScale(coordsSteps_.dx, delta);
    changeOneArgScale(coordsSteps_.dy, delta);
}

Graphics::WindowPoint CoordsSystem::getPosInWindow(const Point& point) const
{
    return Graphics::WindowPoint(center_.x + point.x * coordsSteps_.dx, center_.y + point.y * coordsSteps_.dy);
}

Point CoordsSystem::getPosInCoordsSystem(const Graphics::WindowPoint& point) const
{
    return Point((point.x - center_.x) / coordsSteps_.dx, 
                 (point.y - center_.y) / coordsSteps_.dy, 
                 0);
}

double getDistance3D(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y) + 
                (p1.z - p2.z) * (p1.z - p2.z));
}

double getDistance2D(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y));
}

} // Scene