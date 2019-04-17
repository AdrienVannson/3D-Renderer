#include "Scene.hpp"

using namespace std;


Scene::Scene ()
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

Color Scene::color (const Ray &ray) const
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

    if (isinf(minCollisionDate)) {
        return Color (80, 80, 80); // Return background color
    }

    return object->color(ray);
}
