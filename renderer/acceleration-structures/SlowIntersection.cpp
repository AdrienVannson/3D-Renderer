#include "SlowIntersection.hpp"

SlowIntersection::SlowIntersection ()
{}

SlowIntersection::~SlowIntersection ()
{}

void SlowIntersection::init (Group *objects)
{
    m_objects = objects->objects();
}

Object* SlowIntersection::getObjectIntersecting (const Ray ray)
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

    return object;
}
