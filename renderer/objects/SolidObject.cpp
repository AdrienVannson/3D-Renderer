#include "SolidObject.hpp"
#include "../Scene.hpp"

SolidObject::SolidObject (Scene *scene, const Material &material) :
    Object (scene),
    m_material (material)
{}

Color SolidObject::color (const Ray &ray) const
{
    const Vect intersection = ray.pos() + collisionDate(ray) * ray.dir();

    if (m_material.isMirror()) {
        const Vect n = normal(intersection);
        Vect nextDir = ray.dir() - 2 * (ray.dir() * n) * n;

        Ray nextRay (intersection, nextDir);
        nextRay.moveByEpsilon();

        return m_scene->color(nextRay);
    }

    // TODO: use all lights
    Vect toLight = m_scene->lights()[0]->pos() - intersection;
    toLight.normalize();

    double dotProduct = normal(intersection) * toLight;

    if (dotProduct < 0) {
        return Color(0, 0, 0);
    }

    Ray nextRay (intersection, toLight);
    nextRay.moveByEpsilon();

    if (m_scene->collisionDate(nextRay) < dist(intersection, m_scene->lights()[0]->pos())) {
        return Color (0, 0, 0);
    }

    return Color (dotProduct * m_material.color().red(),
                  dotProduct * m_material.color().green(),
                  dotProduct * m_material.color().blue());
}
