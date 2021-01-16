#ifndef IMPLICITOBJECT_HPP
#define IMPLICITOBJECT_HPP

#include "../SolidObject.hpp"


class ImplicitObject : public SolidObject
{
public:
    ImplicitObject ();
    virtual ~ImplicitObject ();

    double collisionDate (const Ray &ray) const override;
    Vect normal (const Vect &pos) const;
    Collision collision (const Ray &ray) const override;

protected:
    virtual double estimatedDistance (const Vect &pos) const = 0;
};

#endif // IMPLICITOBJECT_HPP
