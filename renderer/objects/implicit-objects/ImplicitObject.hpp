#ifndef IMPLICITOBJECT_HPP
#define IMPLICITOBJECT_HPP

#include "../SolidObject.hpp"


class ImplicitObject : public SolidObject
{
public:
    ImplicitObject (Scene *scene);
    virtual ~ImplicitObject ();

    virtual double collisionDate (const Ray &ray) const;
    virtual Vect normal (const Vect &pos) const;

protected:
    virtual double estimatedDistance (const Vect &pos) const = 0;
};

#endif // IMPLICITOBJECT_HPP
