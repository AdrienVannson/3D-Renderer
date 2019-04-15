#include "Group.hpp"

using namespace std;

Group::Group (Scene *scene) :
    Object (scene)
{}

Group::~Group ()
{}

double Group::collisionDate (const Ray &ray)
{
    double minCollisionDate = INFINITY;

    for (Object *currentObject : m_objects) {
        minCollisionDate = min(currentObject->collisionDate(ray), minCollisionDate);
    }

    return minCollisionDate;
}

Color Group::color (const Ray &ray)
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

    return object->color(ray);
}
