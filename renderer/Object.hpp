#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Box.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Object
{
public:
    Object ();
    virtual ~Object ();

    class Collision
    {
    public:
        Collision () :
            date(INFINITY)
        {}

        double date;
        Vect normal; // At the point of the collision
        Material material;
    };

    virtual Collision collision (const Ray &ray) const = 0;
    double collisionDate (const Ray &ray) const; // Deprecated

    virtual Box boundingBox () const = 0;
};

#endif // OBJECT_HPP
