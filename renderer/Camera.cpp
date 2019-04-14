#include "Camera.hpp"
#include "Scene.hpp"

using namespace std;

Camera::Camera (Scene *scene, const int width, const int height) :
    m_scene (scene),
    m_width (width),
    m_height (height)
{

}

Color Camera::color (const int x, const int y) const
{
    Vect i (m_dir.y(), -m_dir.x());
    i.normalize();

    Vect j (0, 0, 1); // TODO

    Vect dir = m_dir
               + ((double)x/min(m_width, m_height) - 0.5 * m_width / min(m_width, m_height)) * i
               + ((double)y/min(m_width, m_height) - 0.5 * m_height / min(m_width, m_height)) * j;
    dir.normalize();

    Ray ray (m_pos, dir);

    for (Object *object : m_scene->objects()) {
        const double collisionDate = object->collisionDate(ray);

        if (!isinf(collisionDate)) {
            // TODO: no dynamic cast
            const Vect intersection = m_pos + collisionDate*dir;
            Vect normal = intersection - dynamic_cast<Sphere*>(object)->center();
            normal.normalize();

            // TODO: use all lights
            Vect toLight = m_scene->lights()[0]->pos() - dynamic_cast<Sphere*>(object)->center();
            toLight.normalize();

            const double dotProduct = normal * toLight;

            if (dotProduct < 0) {
                return Color(0, 0, 0);
            }

            return Color (dotProduct * dynamic_cast<Sphere*>(object)->material().color().red(),
                          dotProduct * dynamic_cast<Sphere*>(object)->material().color().green(),
                          dotProduct * dynamic_cast<Sphere*>(object)->material().color().blue());
        }
    }

    return Color (100, 100, 100);
}
