#include "GraphicsWindow.hpp"
#include "CoordsSystem.hpp"
#include "LightSource.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

namespace Scene
{

namespace 
{

Graphics::Color calcSpherePixelColor(const CoordsSystem& coordsSystem, const Sphere& sphere, 
                                     const Graphics::WindowPoint& pixelPos, const Graphics::Color& pixelColor,
                                     const Point& lightSourcePos, const Graphics::Color& lightSourceColor)
{
    double z = sphere.calcZ(pixelPos, coordsSystem);

    if (!std::isfinite(z))
        return pixelColor;

    Point spherePointPos = Point{pixelPos.x, pixelPos.y, z};
    Vector normal{sphere.center(), spherePointPos};
    Vector lightVector{spherePointPos, lightSourcePos};

    double cosAngle = cos(normal, lightVector);

    if (cosAngle >= 0)
        return pixelColor + sphere.color() * cosAngle;
    else
        return pixelColor;
}

} // anonymous namespace

void LightSource::highlightSphere(const CoordsSystem& coordsSystem, const Sphere& sphere, 
                                  Graphics::PixelsArray& pixels) const
{
    unsigned int width  = pixels.width();
    unsigned int height = pixels.height();

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            pixels.setPixel(x, y, 
                calcSpherePixelColor(coordsSystem, sphere, Graphics::WindowPoint{x, y}, 
                                     pixels.getPixel(x, y), position_, color_));
        }
    }
}

} // Scene