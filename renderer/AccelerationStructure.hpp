#ifndef ACCELERATIONSTRUCTURE_HPP
#define ACCELERATIONSTRUCTURE_HPP

#include "Object.hpp"

#include <vector>


class AccelerationStructure
{
public:
    AccelerationStructure ();
    virtual ~AccelerationStructure ();

    virtual void init (const std::vector<Object*> &objects) = 0;

    virtual Object* getObjectIntersecting (const Ray ray) = 0;

};

#endif // ACCELERATIONSTRUCTURE_HPP
