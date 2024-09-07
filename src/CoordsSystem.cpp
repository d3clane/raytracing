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

void CoordsSystem::drawSphere(Graphics::Window& window, const Sphere& sphere) const
{
    Graphics::PixelsArray pixelsArray{window.width_, window.height_};

    for (unsigned int y = 0; y < window.height_; ++y)
    {
        for (unsigned int x = 0; x < window.width_; ++x)
        {
            // TODO: function - setPixel

            double z = sphere.calcZ(x, y);
            if (std::isfinite(z))
            {
                Point point{x, y, z};
                pixelsArray.setPixel(x, y, Graphics::Color(10 * z, 0, 0, 255));
            }
            else
                pixelsArray.setPixel(x, y, Graphics::Color(0, 0, 255, 255));
        }
    }

    window.drawPixels(pixelsArray);
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