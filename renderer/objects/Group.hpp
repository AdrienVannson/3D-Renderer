#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include <cmath>

#include "Object.hpp"


class Group : public Object
{
public:
    Group (Scene *scene);
    virtual ~Group ();

    inline void addObject (Object *object) { m_objects.push_back(object); }

    virtual double collisionDate (const Ray &ray) const;
    virtual Color color (const Ray &ray) const;

private:
    std::vector<Object*> m_objects;
};

#endif // GROUP_HPP
