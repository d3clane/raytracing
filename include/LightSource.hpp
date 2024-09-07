#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include "CoordsSystem.hpp"
#include "PixelsArray.hpp"

namespace Scene
{

class LightSource
{
    Point position_;
    Graphics::Color color_;

public:
    LightSource(const Point& position, const Graphics::Color& color) :
        position_(position), color_(color) {}   

    void highlightSphere(const CoordsSystem& coordsSystem, const Sphere& sphere, 
                         Graphics::PixelsArray& pixels) const;
};

} // Scene

#endif // LIGHT_SOURCE_HPP