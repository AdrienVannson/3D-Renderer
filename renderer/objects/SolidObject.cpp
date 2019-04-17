#include "SolidObject.hpp"
#include "../Scene.hpp"

SolidObject::SolidObject (Scene *scene, const Material &material) :
    Object (scene),
    m_material (material)
{}

Color SolidObject::color (const Ray &ray) const
{
    const Vect intersection = ray.pos() + collisionDate(ray) * ray.dir();

    // TODO: use all lights
    Vect toLight = m_scene->lights()[0]->pos() - intersection;
    toLight.normalize();

    double dotProduct = normal(intersection) * toLight;

    if (dotProduct < 0) {
        return Color(0, 0, 0);
    }

    return Color (dotProduct * m_material.color().red(),
                  dotProduct * m_material.color().green(),
                  dotProduct * m_material.color().blue());
}
