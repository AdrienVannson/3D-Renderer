#include "Sphere.hpp"
#include "../Scene.hpp"

Sphere::Sphere (Scene *scene, const Vect &center, const double radius, const Material &material) :
    Object (scene),

    m_center (center),
    m_radius (radius),
    m_material (material)
{}

Sphere::~Sphere ()
{}

double Sphere::collisionDate (const Ray &ray)
{
    const Vect AB = m_center - ray.pos();
    const Vect v = ray.dir();

    const double delta = (AB*v) * (AB*v) + (m_radius*m_radius - AB*AB) * v*v;

    if (delta < 0) {
        return INFINITY;
    }

    const double root1 = (AB*v - sqrt(delta)) / (v*v);
    if (root1 >= 0) {
        return root1;
    }

    const double root2 = (AB*v + sqrt(delta)) / (v*v);
    if (root2 >= 0) {
        return root2;
    }

    return INFINITY;
}

Color Sphere::color (const Ray &ray)
{
    const Vect intersection = ray.pos() + collisionDate(ray) * ray.dir();
    Vect normal = intersection - m_center;
    normal.normalize();

    // TODO: use all lights
    Vect toLight = m_scene->lights()[0]->pos() - intersection;
    toLight.normalize();

    const double dotProduct = normal * toLight;

    if (dotProduct < 0) {
        return Color(0, 0, 0);
    }

    return Color (dotProduct * m_material.color().red(),
                  dotProduct * m_material.color().green(),
                  dotProduct * m_material.color().blue());
}
