#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "SolidObject.hpp"
#include "../Material.hpp"


class Sphere : public SolidObject
{
public:
    Sphere (Scene *scene, const Vect &center=Vect(), const double radius=1, const Material &material=Material());
    virtual ~Sphere ();

    inline Vect center () const { return m_center; }
    inline void setCenter (const Vect &center) { m_center = center; }

    inline double radius () const { return m_radius; }
    inline void setRadius (const double radius) { m_radius = radius; }

    virtual double collisionDate (const Ray &ray);
    virtual Color color (const Ray &ray);

private:
    Vect m_center;
    double m_radius;
};

#endif // SPHERE_HPP
