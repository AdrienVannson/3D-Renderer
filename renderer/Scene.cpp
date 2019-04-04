#include "Scene.hpp"

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
}
