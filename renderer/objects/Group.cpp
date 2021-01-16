#include "Group.hpp"

using namespace std;

Group::Group ()
{}

Group::~Group ()
{}

Group* Group::withoutInternGroups ()
{
    Group *root = new Group ();
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
    double minDate = INFINITY;

    // Select nearest object
    for (Object *currentObject : m_objects) {
        minDate = min(currentObject->collisionDate(ray), minDate);
    }

    return minDate;
}

Object::Collision Group::collision (const Ray &ray) const
{
    Collision minCol;
    minCol.date = INFINITY;

    // Select nearest object
    for (Object *currentObject : m_objects) {
        Collision col = currentObject->collision(ray);

        if (col.date < minCol.date) {
            minCol = col;
        }
    }

    return minCol;
}

Box Group::boundingBox() const
{
    Box res;

    for (Object* obj : m_objects) {
        res = res + obj->boundingBox();
    }

    return res;
}
