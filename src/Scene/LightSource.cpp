#include "Graphics/GraphicsWindow.hpp"
#include "Scene/CoordsSystem.hpp"
#include "Scene/LightSource.hpp"
#include "Scene/Sphere.hpp"
#include "Scene/Vector.hpp"

namespace Scene
{

namespace 
{

inline Graphics::Color calcLambertColor(
    const Point& spherePointPos, const Sphere& sphere,
    const Point& lightPos, const Graphics::Color& lightColor,
    const Graphics::Color& ambientColor
)
{
    Vector normal{sphere.center(), spherePointPos};
    Vector lightVector{spherePointPos, lightPos};

    double cosAngle = cos(normal, lightVector);
    if (cosAngle < 0) cosAngle = 0;

    return ambientColor * sphere.color() + sphere.color() * lightColor * cosAngle;
}

inline Graphics::Color calcBlinkColor(
    const Point& spherePointPos, const Sphere& sphere, 
    const Point& lightSourcePos, const Graphics::Color& lightSourceColor,
    const Camera& camera
)
{
    Vector normal{sphere.center(), spherePointPos};
    Vector lightVector{spherePointPos, lightSourcePos};
    Vector viewVector{spherePointPos, camera.pos()};
    Vector reflected = lightVector.reflectRelatively(normal);

    double cosAngle = cos(reflected, viewVector);
    if (cosAngle < 0) cosAngle = 0;

    return lightSourceColor * std::pow(cosAngle, 25); // magic 25
}

Graphics::Color calcSpherePixelColor(
    const CoordsSystem& coordsSystem, const Sphere& sphere,
    const Camera& camera, const Graphics::WindowPoint& pixelPos, const Graphics::Color& pixelColor,
    const Point& lightSourcePos, const Graphics::Color& lightSourceColor
)
{
    double z = sphere.calcZ(pixelPos, coordsSystem);

    if (!std::isfinite(z))
        return pixelColor;

    Point spherePointPos = Point{pixelPos.x, pixelPos.y, z};
    Vector normal{sphere.center(), spherePointPos};
    Vector lightVector{spherePointPos, lightSourcePos};

    Graphics::Color resultColor = pixelColor;
    
    Graphics::Color ambientColor = Graphics::Color{10, 10, 10, 255}; // shadow
    resultColor = resultColor + calcLambertColor(
        spherePointPos, sphere, lightSourcePos, lightSourceColor, ambientColor
    );

    resultColor = resultColor + calcBlinkColor(
        spherePointPos, sphere, lightSourcePos, lightSourceColor, camera
    );
    
    return resultColor;
}

} // namespace anonymous

void LightSource::highlightSphere(
    const CoordsSystem& coordsSystem, const Sphere& sphere, const Camera& camera, Graphics::PixelsArray& pixels
) const
{
    unsigned int width  = pixels.width();
    unsigned int height = pixels.height();

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            pixels.setPixel(
                x, y, 
                calcSpherePixelColor(
                    coordsSystem, sphere, camera, 
                    Graphics::WindowPoint{x, y}, pixels.getPixel(x, y), 
                    pos_, color_
                )
            );
        }
    }
}

void LightSource::move  (const Vector& delta) { pos_ = pos_ + delta; }
void LightSource::setPos(const Point&  pos  ) { pos_ = pos;               }

} // Scene