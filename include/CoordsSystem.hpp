#ifndef COORDS_SYSTEM_HPP
#define COORDS_SYSTEM_HPP

#include "GraphicsWindow.hpp"

namespace Scene
{

struct Point
{
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

class CoordsSystem
{
    Graphics::Point center_;
    
    unsigned int stepX, stepY;

public:

    CoordsSystem(unsigned int stepX, unsigned int stepY, const Graphics::Point& center) : 
        stepX(stepX), stepY(stepY), center_(center) {}

    void moveCenter (const Graphics::Point& delta);
    void changeScale(const int delta);

    Graphics::Point getPosInWindow      (const Point& point) const;
    Point           getPosInCoordsSystem(const Graphics::Point& point) const;
};

} // Scene

#endif // COORDS_SYSTEM_HPP