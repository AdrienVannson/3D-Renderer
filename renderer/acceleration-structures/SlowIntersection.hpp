#ifndef SLOWINTERSECTION_HPP
#define SLOWINTERSECTION_HPP

#include "../AccelerationStructure.hpp"


class SlowIntersection : public AccelerationStructure
{
public:
    SlowIntersection ();
    virtual ~SlowIntersection ();

    virtual void init (Group *objects) override;

    virtual Object* getObjectIntersecting (const Ray ray) override;

private:
    std::vector<Object*> m_objects;
};

#endif // SLOWINTERSECTION_HPP
