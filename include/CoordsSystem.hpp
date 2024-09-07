#ifndef COORDS_SYSTEM_HPP
#define COORDS_SYSTEM_HPP

#include "GraphicsWindow.hpp"

namespace Scene
{

struct Point
{
    double x, y, z;

    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    //Point(Graphics::WindowPoint windowPoint) : x(windowPoint.x), y(windowPoint.y), z(0) {}
};

class Sphere;

struct PixelVector
{
    int dx, dy, dz;

    PixelVector(int dx, int dy, int dz) : dx(dx), dy(dy), dz(dz) {}
};

class CoordsSystem
{
    Point center_;
    PixelVector coordsSteps_;

public:
    CoordsSystem(const PixelVector& coordsSteps, const Point& center) : 
        coordsSteps_(coordsSteps), center_(center) {}

    void moveCenter (const Graphics::WindowPoint& delta);
    void changeScale(const int delta);

    void drawSphere(Graphics::Window& window, const Sphere& sphere) const;

    Graphics::WindowPoint getPosInWindow(const Point& point) const;

    Point getPosInCoordsSystem(const Graphics::WindowPoint& point) const;
};

double getDistance3D(const Point& p1, const Point& p2);
double getDistance2D(const Point& p1, const Point& p2);

} // Scene

#endif // COORDS_SYSTEM_HPP