#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "Object.hpp"
#include "../Material.hpp"


class Sphere : public Object
{
public:
    Sphere (const Vect &center=Vect(), const double radius=1, const Material &material=Material());
    virtual ~Sphere ();

    inline Vect center () const { return m_center; }
    inline void setCenter (const Vect &center) { m_center = center; }

    inline double radius () const { return m_radius; }
    inline void setRadius (const double radius) { m_radius = radius; }

    inline Material material () const { return m_material; }
    inline void setMaterial (const Material &material) { m_material = material; }

    virtual double collisionDate (const Ray &ray);

private:
    Vect m_center;
    double m_radius;

    Material m_material;
};

#endif // SPHERE_HPP
