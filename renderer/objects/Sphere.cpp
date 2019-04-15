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

    const double root1 = (AB*v - sqrt(delta)) / (v*v);
    if (root1 >= 0) {
        return root1;
    }

    const double root2 = (AB*v + sqrt(delta)) / (v*v);
    if (root2 >= 0) {
        return root2;
    }

    return INFINITY;
}
