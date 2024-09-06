#include "CoordsSystem.hpp"

namespace Scene
{

namespace 
{

void changeOneArgScale(unsigned int& step, const int delta);

void changeOneArgScale(unsigned int& step, const int delta)
{
    if (delta < 0 && step <= -delta) step = 1;
    else step += delta;
}

} // anonymous namespace

using Graphics::Line;

void CoordsSystem::moveCenter (const Graphics::Point& delta)
{
    center_.x += delta.x;
    center_.y += delta.y;
}

void CoordsSystem::changeScale(const int delta)
{
    changeOneArgScale(stepX, delta);
    changeOneArgScale(stepY, delta);
}

Graphics::Point CoordsSystem::getPosInWindow(const Point& point) const
{
    return Graphics::Point(center_.x + point.x * stepX, center_.y + point.y * stepY);
}

Point CoordsSystem::getPosInCoordsSystem(const Graphics::Point& point) const
{
    return Point((point.x - center_.x) / stepX, (point.y - center_.y) / stepY);
}

} // Scene