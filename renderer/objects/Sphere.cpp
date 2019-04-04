#include "Sphere.hpp"

Sphere::Sphere (const Vect &center, const double radius) :
    m_center (center),
    m_radius (radius)
{}

Sphere::~Sphere ()
{}

double Sphere::collisionDate (const Ray &ray)
{
    return INFINITY;
}
