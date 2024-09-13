#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include "Graphics/PixelsArray.hpp"
#include "Scene/CoordsSystem.hpp"
#include "Scene/Camera.hpp"

#include "Scene/Transformable.hpp"

namespace Scene
{

class LightSource : public Transformable
{
    Point pos_;
    Graphics::Color color_;

public:
    LightSource(const Point& position, const Graphics::Color& color) :
        pos_(position), color_(color) {}   

    Graphics::Color color() const { return color_; }
    
    void highlightSphere(const CoordsSystem& coordsSystem, const Sphere& sphere, 
                         const Camera& camera, Graphics::PixelsArray& pixels) const;

    virtual void move  (const Vector& delta) override;
    virtual void setPos(const Point&  pos  ) override;
};

} // Scene

#endif // LIGHT_SOURCE_HPP