#include "ImplicitObject.hpp"

ImplicitObject::ImplicitObject ()
{}

ImplicitObject::~ImplicitObject ()
{}

double ImplicitObject::collisionDate (const Ray &ray) const
{
    double t = 0;

    while (true) {
        const double dist = estimatedDistance(ray.pos() + t*ray.dir());
        t += dist;

        if (t > 100) {
            return INFINITY;
        }

        if (dist < 1e-6) {
            return t;
        }
    }
}

Vect ImplicitObject::normal (const Vect &pos) const
{
    Vect normal;

    const double eps = 0.001;

    normal.setX( estimatedDistance(pos + Vect(eps, 0, 0)) - estimatedDistance(pos - Vect(eps, 0, 0)) );
    normal.setY( estimatedDistance(pos + Vect(0, eps, 0)) - estimatedDistance(pos - Vect(0, eps, 0)) );
    normal.setZ( estimatedDistance(pos + Vect(0, 0, eps)) - estimatedDistance(pos - Vect(0, 0, eps)) );

    normal.normalize();
    return normal;
}

Object::Collision ImplicitObject::collision (const Ray &ray) const
{
    Collision col;
    col.date = collisionDate(ray);
    col.normal = normal(ray.pos() + col.date*ray.dir());
    col.material = m_material;
    return col;
}
