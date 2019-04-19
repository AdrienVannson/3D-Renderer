#include "Scene.hpp"

using namespace std;


Scene::Scene () :
    m_backgroundColor (Color(80, 80, 80))
{
    m_camera = new Camera (this);
}

Scene::~Scene ()
{
    delete m_camera;

    for (Object *object : m_objects) {
        delete object;
    }

    for (Light *light : m_lights) {
        delete light;
    }
}

double Scene::collisionDate (const Ray &ray) const
{
    double minCollisionDate = INFINITY;

    for (Object *object : m_objects) {
        minCollisionDate = min(object->collisionDate(ray), minCollisionDate);
    }

    return minCollisionDate;
}

Color Scene::color (const Ray &ray, const int remainingDepth) const
{
    if (remainingDepth == 0) {
        return m_backgroundColor;
    }

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

    if (isinf(minCollisionDate)) {
        return m_backgroundColor;
    }

    return object->color(ray, remainingDepth);
}
