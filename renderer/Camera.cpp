#include "Camera.hpp"
#include "Scene.hpp"

Camera::Camera (Scene *scene, const int width, const int height) :
    m_scene (scene),
    m_width (width),
    m_height (height)
{

}

Color Camera::color (const int x, const int y) const
{
    Vect i (m_dir.x(), -m_dir.y());
    i.normalize();

    Vect j (0, 0, 0); // TODO

    const Vect dir = m_dir + (x - 0.5*m_width) * i + (y - 0.5*m_height) * j;

    Ray ray (m_pos, dir);

    return Color (0, 0, 255);
}
