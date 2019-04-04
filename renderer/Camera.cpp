#include "Camera.hpp"
#include "Scene.hpp"

Camera::Camera (Scene *scene, const int width, const int height) :
    m_scene (scene),
    m_width (width),
    m_height (height)
{

}
