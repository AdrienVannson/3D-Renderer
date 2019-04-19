#include "Camera.hpp"
#include "Scene.hpp"

using namespace std;

Camera::Camera (Scene *scene, const int width, const int height) :
    m_scene (scene),
    m_width (width),
    m_height (height)
{

}

Color Camera::color (const int x, const int y, const int remainingDepth) const
{
    Vect i (m_dir.y(), -m_dir.x());
    i.normalize();

    Vect j = m_dir ^ i;
    j.normalize();

    if (j.z() < 0) {
        j *= -1;
    }

    Vect dir = m_dir
               + ((double)x/min(m_width, m_height) - 0.5 * m_width / min(m_width, m_height)) * i
               + ((double)y/min(m_width, m_height) - 0.5 * m_height / min(m_width, m_height)) * j;
    dir.normalize();

    return m_scene->color(Ray(m_pos, dir), remainingDepth);
}
