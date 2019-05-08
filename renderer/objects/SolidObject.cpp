#include "SolidObject.hpp"
#include "../Scene.hpp"

#include <algorithm>

using namespace std;

SolidObject::SolidObject (Scene *scene, const Material &material) :
    Object (scene),
    m_material (material)
{}

Color SolidObject::color (const Ray &ray, const int remainingDepth) const
{
    const Vect intersection = ray.pos() + collisionDate(ray) * ray.dir();

    Color finalColor;

    for (const Light *light : m_scene->lights()) {
        Vect toLight = light->pos() - intersection;
        toLight.normalize();

        double dotProduct = normal(intersection) * toLight;

        if (dotProduct >= 0) {
            Ray nextRay (intersection, toLight);
            nextRay.moveByEpsilon();

            if (m_scene->collisionDate(nextRay) >= dist(intersection, m_scene->lights()[0]->pos())) {
                Color color (dotProduct * m_material.color().red(),
                             dotProduct * m_material.color().green(),
                             dotProduct * m_material.color().blue());
                color *= light->intensity();

                finalColor += color;
            }
        }
    }

    // Reflection
    if (m_material.reflectionCoef() != 0) {
        const Vect n = normal(intersection);
        Vect nextDir = ray.dir() - 2 * (ray.dir() * n) * n;

        Ray nextRay (intersection, nextDir);
        nextRay.moveByEpsilon();

        Color nextColor = m_scene->color(nextRay, remainingDepth-1);
        nextColor *= m_material.reflectionCoef();

        finalColor += nextColor;
    }

    // Refraction
    if (m_material.refractionCoef() != 0) {
        Vect n = normal(intersection);

        // Snell's law
        double n1 = 1;
        double n2 = material().refractiveIndex();

        double cosTheta1 = ray.dir() * n;

        if (cosTheta1 < 0) {
            cosTheta1 = -cosTheta1;
        }
        else {
            swap(n1, n2);
            n *= -1;
        }

        const double r = n1 / n2;
        const double k = 1 - r*r * (1 - cosTheta1*cosTheta1);

        if (k >= 0) { // No refraction otherwise
            Vect nextDir = r * ray.dir() + (r * cosTheta1 - sqrt(k)) * n;
            nextDir.normalize();

            Ray nextRay (intersection, nextDir);
            nextRay.moveByEpsilon();

            Color nextColor = m_scene->color(nextRay, remainingDepth-1);
            nextColor *= m_material.refractionCoef();

            finalColor += nextColor;
        }
    }

    return finalColor;
}
