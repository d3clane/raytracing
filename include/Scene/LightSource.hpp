#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include "Graphics/PixelsArray.hpp"
#include "Scene/CoordsSystem.hpp"
#include "Scene/Camera.hpp"

namespace Scene
{

class LightSource
{
    Point position_;
    Graphics::Color color_;

public:
    LightSource(const Point& position, const Graphics::Color& color) :
        position_(position), color_(color) {}   

    Graphics::Color color() const { return color_; }
    
    void highlightSphere(const CoordsSystem& coordsSystem, const Sphere& sphere, 
                         const Camera& camera, Graphics::PixelsArray& pixels) const;
};

} // Scene

#endif // LIGHT_SOURCE_HPP