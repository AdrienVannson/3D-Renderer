#include "Scene.hpp"

Scene::Scene ()
{
    m_camera = new Camera (this);
}

Scene::~Scene ()
{
    delete m_camera;
    m_camera = 0;
}
