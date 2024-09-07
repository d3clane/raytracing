#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>

#include "CoordsSystem.hpp"

namespace Scene
{

struct Vector
{
    double dx, dy, dz;

    Vector(double dx, double dy, double dz) : dx(dx), dy(dy), dz(dz) {}
    Vector(const Point& begin, const Point& end) : 
        dx(end.x - begin.x), dy(end.y - begin.y), dz(end.z - begin.z) {}

    double length() const;

    Vector operator - () const;
    Vector operator + (const Vector& other) const;
    Vector operator - (const Vector& other) const;
    Vector operator * (const double coeff)  const;
    Vector operator / (const double coeff)  const;

    double operator ^ (const Vector& other) const;
};

double cos(const Vector& v1, const Vector& v2);

} // Scene

#endif // VECTOR_HPP