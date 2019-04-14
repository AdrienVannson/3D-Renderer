#include "Sphere.hpp"

Sphere::Sphere (const Vect &center, const double radius, const Material &material) :
    m_center (center),
    m_radius (radius),
    m_material (material)
{}

Sphere::~Sphere ()
{}

double Sphere::collisionDate (const Ray &ray)
{
    Vect pos = ray.pos();

    for (int i=0; i<500; i++) {
        if (dist(pos, m_center) <= m_radius) {
            return i/100.0;
        }
        pos = pos + 0.01*ray.dir();
    }

    return INFINITY;
}
