#include "Sphere.hpp"
#include "../Scene.hpp"

Sphere::Sphere (const Vect &center, const double radius, const Material &material) :
    SolidObject(material),
    m_center (center),
    m_radius (radius)
{}

Sphere::~Sphere ()
{}

double Sphere::collisionDate (const Ray &ray) const
{
    const Vect AB = m_center - ray.pos();
    const Vect v = ray.dir();

    const double delta = (AB*v) * (AB*v) + (m_radius*m_radius - AB*AB) * v*v;

    if (delta <= 0) {
        return INFINITY;
    }

    const double root1 = (AB*v - sqrt(delta)) / (v*v);
    if (root1 > 0) {
        return root1;
    }

    const double root2 = (AB*v + sqrt(delta)) / (v*v);
    if (root2 > 0) {
        return root2;
    }

    return INFINITY;
}

Vect Sphere::normal (const Vect &pos) const
{
    Vect normal = pos - m_center;
    normal.normalize();
    return normal;
}

Object::Collision Sphere::collision (const Ray &ray) const
{
    Collision col;
    col.date = collisionDate(ray);
    col.normal = normal(ray.pos() + col.date*ray.dir());
    col.material = m_material;
    return col;
}

Box Sphere::boundingBox () const
{
    return Box {m_center - Vect(m_radius, m_radius, m_radius),
                m_center + Vect(m_radius, m_radius, m_radius)};
}
