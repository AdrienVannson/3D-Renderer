#ifndef OCTREE_HPP
#define OCTREE_HPP

#include "../AccelerationStructure.hpp"


class Octree : public AccelerationStructure
{
public:
    Octree ();
    virtual ~Octree ();

    virtual void init (const std::vector<Object*> &objects) override;

    virtual Object* getObjectIntersecting (const Ray ray) override;

private:
    struct Node;

    Object* getObjectIntersecting (const Ray &ray, const Node *node);

    Node *m_root;
};

#endif // OCTREE_HPP
