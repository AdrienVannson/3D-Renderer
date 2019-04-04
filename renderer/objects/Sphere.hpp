#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "Object.hpp"


class Sphere : public Object
{
public:
    Sphere (const Vect &center=Vect(), const double radius=1);
    virtual ~Sphere ();

    inline Vect& center () { return m_center; }
    inline Vect center () const { return m_center; }

    inline double& radius () { return m_radius; }
    inline double radius () const { return m_radius; }

    virtual double collisionDate (const Ray &ray);

private:
    Vect m_center;
    double m_radius;
};

#endif // SPHERE_HPP
