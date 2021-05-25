#include "Renderer.hpp"
#include "Scene.hpp"

Renderer::Renderer (Scene *scene) :
    m_scene(scene)
{}

Renderer::~Renderer ()
{}

Color Renderer::color(const Ray &ray, const int remainingDepth)
{
    if (remainingDepth == 0) {
        return m_scene->backgroundColor();
    }

    Object *object = m_scene->accelerationStructure()->getObjectIntersecting(ray);
    if (object == 0) {
        return m_scene->backgroundColor();
    }

    const Object::Collision collision = object->collision(ray);

    const Vect intersection = ray.pos() + collision.date*ray.dir();

    Color finalColor;

    for (const Light *light : m_scene->lights()) {
        Vect toLight = light->pos() - intersection;
        toLight.normalize();

        double dotProduct = collision.normal * toLight;

        if (dotProduct >= 0) {
            Ray nextRay (intersection, toLight);
            nextRay.moveByEpsilon();

            if (m_scene->collisionDate(nextRay) >= Vect::dist(intersection, light->pos())) {
                Color color (dotProduct * collision.material.color().red(),
                             dotProduct * collision.material.color().green(),
                             dotProduct * collision.material.color().blue());
                color *= light->intensity();

                finalColor += color;
            }
        }
    }

    // Reflection
    if (collision.material.reflectionCoef() != 0) {
        const Vect n = collision.normal;
        Vect nextDir = ray.dir() - 2 * (ray.dir() * n) * n;

        Ray nextRay (intersection, nextDir);
        nextRay.moveByEpsilon();

        Color nextColor = color(nextRay, remainingDepth-1);
        nextColor *= collision.material.reflectionCoef();

        finalColor += nextColor;
    }

    // Refraction
    if (collision.material.refractionCoef() != 0) {
        Vect n = collision.normal;

        // Snell's law
        double n1 = 1;
        double n2 = collision.material.refractiveIndex();

        double cosTheta1 = ray.dir() * n;

        if (cosTheta1 < 0) {
            cosTheta1 = -cosTheta1;
        }
        else {
            std::swap(n1, n2);
            n *= -1;
        }

        const double r = n1 / n2;
        const double k = 1 - r*r * (1 - cosTheta1*cosTheta1);

        if (k >= 0) { // No refraction otherwise
            Vect nextDir = r * ray.dir() + (r * cosTheta1 - sqrt(k)) * n;
            nextDir.normalize();

            Ray nextRay (intersection, nextDir);
            nextRay.moveByEpsilon();

            Color nextColor = color(nextRay, remainingDepth-1);
            nextColor *= collision.material.refractionCoef();

            finalColor += nextColor;
        }
    }

    return finalColor;
}
