#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Scene/CoordsSystem.hpp"
#include "Scene/Transformable.hpp"

namespace Scene
{

class Camera : public Transformable
{
    Point pos_;

public:
    Camera(const Point& pos) : pos_(pos) {}

    inline Point pos() const { return pos_; }
    
    void drawPixels(Graphics::Window& window, const CoordsSystem& coordsSystem, 
                    const Graphics::PixelsArray& pixelsArray) const;

    virtual void move  (const Vector& delta) override;
    virtual void setPos(const Point&  pos  ) override;
};

} // Scene

#endif // CAMERA_HPP