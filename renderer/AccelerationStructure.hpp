#ifndef ACCELERATIONSTRUCTURE_HPP
#define ACCELERATIONSTRUCTURE_HPP

#include "objects/Group.hpp"

#include <vector>


class AccelerationStructure
{
public:
    AccelerationStructure ();
    virtual ~AccelerationStructure ();

    virtual void init (Group *objects) = 0;

    virtual Object* getObjectIntersecting (const Ray ray) = 0;

};

#endif // ACCELERATIONSTRUCTURE_HPP
