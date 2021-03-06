#include "Camera.hpp"
#include "Scene.hpp"

using namespace std;

Camera::Camera(const int width, const int height) :
    m_width (width),
    m_height (height)
{}

Image* Camera::image (Renderer *renderer) const
{
    Image *image = new Image (m_width, m_height);

    for (int x=0; x<m_width; x++) {
        for (int y=0; y<m_height; y++) {
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

            image->setColor(x, y, renderer->color(Ray(m_pos, dir), 10));
        }
    }

    return image;
}
