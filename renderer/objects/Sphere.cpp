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
    const Vect AB = m_center - ray.pos();
    const Vect v = ray.dir();

    const double delta = (AB*v) * (AB*v) + (m_radius*m_radius - AB*AB) * v*v;

    if (delta < 0) {
        return INFINITY;
    }

    return (AB*v - sqrt(delta)) / (v*v);
}
