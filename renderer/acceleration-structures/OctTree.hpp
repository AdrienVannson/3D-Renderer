#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include "../AccelerationStructure.hpp"


class OctTree : public AccelerationStructure
{
public:
    OctTree ();
    virtual ~OctTree ();

    virtual void init (const std::vector<Object*> &objects) override;

    virtual Object* getObjectIntersecting (const Ray ray) override;

private:
    struct Node;

    Object* getObjectIntersecting (const Ray &ray, const Node *node);

    Node *m_root;
};

#endif // OCTTREE_HPP
