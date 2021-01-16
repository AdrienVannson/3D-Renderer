#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "SolidObject.hpp"
#include "../Material.hpp"


class Sphere : public SolidObject
{
public:
    Sphere (const Vect &center=Vect(), const double radius=1, const Material &material=Material());
    virtual ~Sphere ();

    inline Vect center () const { return m_center; }
    inline void setCenter (const Vect &center) { m_center = center; }

    inline double radius () const { return m_radius; }
    inline void setRadius (const double radius) { m_radius = radius; }

    double collisionDate (const Ray &ray) const;
    Vect normal (const Vect &pos) const;
    Collision collision (const Ray &ray) const override;

    virtual Box boundingBox () const override;

private:
    Vect m_center;
    double m_radius;
};

#endif // SPHERE_HPP
