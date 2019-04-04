#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../Ray.hpp"


class Object
{
public:
    Object ();
    virtual ~Object ();

    virtual double collisionDate (const Ray &ray) = 0;

};

#endif // OBJECT_HPP
