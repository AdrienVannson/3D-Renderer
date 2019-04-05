#include "Sphere.hpp"

Sphere::Sphere (const Vect &center, const double radius) :
    m_center (center),
    m_radius (radius)
{}

Sphere::~Sphere ()
{}

double Sphere::collisionDate (const Ray &ray)
{
    Vect pos = ray.pos();

    for (int i=0; i<100; i++) {
        if (dist(pos, m_center) <= m_radius) {
            return i*10;
        }
        pos = pos + 0.1*ray.dir();
    }

    return INFINITY;
}
