#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Graphics/PixelsArray.hpp"

#include "Scene/CoordsSystem.hpp"
#include "Scene/Vector.hpp"
#include "Scene/Transformable.hpp"

namespace Scene
{

class Sphere : public Transformable
{
    Point center_;
    double radius_;
    Graphics::Color color_;

public:
    Sphere(const Point& center, const double radius, const Graphics::Color& color);

    bool isInside(const Point& point) const;

    Point center() const { return center_; }

    Graphics::Color color() const     { return color_;  }
    void color(Graphics::Color color) { color_ = color; }
    
    double calcZ(const Graphics::WindowPoint& windowPoint, const CoordsSystem& coordsSystem) const;
    double calcZ(const double x, const double y) const; 

    virtual void move  (const Vector& delta ) override;
    virtual void setPos(const Point&  center) override;  
};

} // Scene


#endif // SPHERE_HPP