#include "Octree.hpp"

struct Octree::Node
{
    Node ();
    ~Node ();

    void createChildren (const int remainingDepth);
    void updateBox ();

    Node* children[8];

    Box box;
    std::vector<Object*> objects;
};


Octree::Octree ()
{}

Octree::~Octree ()
{
    delete m_root;
}

void Octree::init (const std::vector<Object*> &objects)
{
    delete m_root;
    m_root = new Node;

    m_root->objects = objects;
    m_root->updateBox();

    m_root->createChildren(3);
}

Object* Octree::getObjectIntersecting (const Ray ray)
{
    return getObjectIntersecting(ray, m_root);
}

Object* Octree::getObjectIntersecting (const Ray &ray, const Node *node)
{
    if (node->box.collisionDate(ray) == INFINITY) {
        return 0;
    }

    Object *nearestObject = 0;
    double minCollisionDate = INFINITY;

    for (Object *obj : node->objects) {
        const double collisionDate = obj->collisionDate(ray);

        if (collisionDate < minCollisionDate) {
            minCollisionDate = collisionDate;
            nearestObject = obj;
        }
    }

    if (node->children[0]) {
        for (int child=0; child<8; child++) {
            Object *obj = getObjectIntersecting(ray, node->children[child]);

            if (obj == 0) continue;

            const double collisionDate = obj->collisionDate(ray);

            if (collisionDate < minCollisionDate) {
                minCollisionDate = collisionDate;
                nearestObject = obj;
            }
        }
    }

    return nearestObject;
}


/*
 * Node
 */

Octree::Node::Node ()
{
    for (int i=0; i<8; i++) children[i] = 0;
}

Octree::Node::~Node ()
{
    for (int i=0; i<8; i++) {
        delete children[i];
    }
}

void Octree::Node::createChildren (const int remainingDepth)
{
    if (remainingDepth == 0) return;
    if (objects.size() < 300) return; // TODO : change

    for (int i=0; i<8; i++) {
        children[i] = new Node;
    }

    const Vect t = 0.5 * (box.maxVertex() - box.minVertex());

    children[0]->box = Box(box.minVertex() + Vect(0, 0, 0), Vect());
    children[1]->box = Box(box.minVertex() + Vect(0, 0, t.z()), Vect());
    children[2]->box = Box(box.minVertex() + Vect(0, t.y(), 0), Vect());
    children[3]->box = Box(box.minVertex() + Vect(0, t.y(), t.z()), Vect());
    children[4]->box = Box(box.minVertex() + Vect(t.x(), 0, 0), Vect());
    children[5]->box = Box(box.minVertex() + Vect(t.x(), 0, t.z()), Vect());
    children[6]->box = Box(box.minVertex() + Vect(t.x(), t.y(), 0), Vect());
    children[7]->box = Box(box.minVertex() + Vect(t.x(), t.y(), t.z()), Vect());

    for (int child=0; child<8; child++) {
        children[child]->box.setMaxVertex(children[child]->box.minVertex() + t);
    }

    // Add objects to children
    for (int child=0; child<8; child++) {
        for (Object *obj : objects) {
            if (! (obj->boundingBox() * children[child]->box) .isEmpty()) {
                children[child]->objects.push_back(obj);
            }
        }
        children[child]->updateBox();
    }

    objects.clear();

    for (int child=0; child<8; child++) {
        children[child]->createChildren(remainingDepth-1);
    }
}

void Octree::Node::updateBox ()
{
    box.reset();
    for (Object *object : objects) {
        box = box + object->boundingBox();
    }
}
