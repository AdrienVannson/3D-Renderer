#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include <cmath>

#include "../Object.hpp"


class Group : public Object
{
public:
    Group ();
    virtual ~Group ();

    inline void addObject (Object *object) { m_objects.push_back(object); }

    inline int size () const { return m_objects.size(); }
    inline const std::vector<Object*>& objects () const { return m_objects; }

    Group* withoutInternGroups ();
    void addObjectWithoutInternGroups (Object *object);

    double collisionDate (const Ray &ray) const override;
    Collision collision (const Ray &ray) const override;

    virtual Box boundingBox() const override;

private:
    std::vector<Object*> m_objects;
};

#endif // GROUP_HPP
