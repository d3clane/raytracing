#include <cassert>
#include <cmath>

#include "Vector.hpp"

namespace Scene
{

double cos(const Vector& v1, const Vector& v2)
{
    return v1 ^ v2 / v1.length() / v2.length(); 
}

double Vector::length() const
{
    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vector Vector::operator - () const
{
    return Vector(-dx, -dy, -dz);
}

Vector Vector::operator + (const Vector& other) const
{
    return Vector(dx + other.dx, dy + other.dy, dz + other.dz);   
}

Vector Vector::operator - (const Vector& other) const
{  
    return *this + (-other);
}

Vector Vector::operator * (const double coeff)  const
{
    assert(std::isfinite(coeff));

    return Vector(dx * coeff, dy * coeff, dz * coeff);
}

Vector Vector::operator / (const double coeff)  const
{
    assert(std::isfinite(coeff));
    assert(coeff != 0);

    return Vector(dx / coeff, dy / coeff, dz / coeff);
}

double Vector::operator ^ (const Vector& other) const   
{
    return dx * other.dx + dy * other.dy + dz * other.dz;
}

} // Scene