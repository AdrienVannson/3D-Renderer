#include "Group.hpp"

using namespace std;

Group::Group (Scene *scene) :
    Object (scene)
{}

Group::~Group ()
{}

Group* Group::withoutInternGroups ()
{
    Group *root = new Group (m_scene);
    root->addObjectWithoutInternGroups(this);
    return root;
}

void Group::addObjectWithoutInternGroups (Object *object)
{
    Group *g = dynamic_cast<Group*>(object);

    if (g == 0) {
        addObject(object);
    }
    else {
        for (Object *child : g->objects()) {
            addObjectWithoutInternGroups(child);
        }
    }
}

double Group::collisionDate (const Ray &ray) const
{
    double minCollisionDate = INFINITY;

    for (Object *currentObject : m_objects) {
        minCollisionDate = min(currentObject->collisionDate(ray), minCollisionDate);
    }

    return minCollisionDate;
}

Color Group::color (const Ray &ray, const int remainingDepth) const
{
    Object *object = 0;
    double minCollisionDate = INFINITY;

    // Select nearest object
    for (Object *currentObject : m_objects) {
        const double collisionDate = currentObject->collisionDate(ray);

        if (collisionDate < minCollisionDate) {
            minCollisionDate = collisionDate;
            object = currentObject;
        }
    }

    return object->color(ray, remainingDepth);
}

Box Group::boundingBox() const
{
    Box res;

    for (Object* obj : m_objects) {
        res = res + obj->boundingBox();
    }

    return res;
}
