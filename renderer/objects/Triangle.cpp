#include "Triangle.hpp"
#include "../Scene.hpp"

Triangle::Triangle (Scene *scene, const Vect &A, const Vect &B, const Vect &C, const Material &material) :
    Object (scene),

    m_A (A),
    m_B (B),
    m_C (C),
    m_material (material)
{}

Triangle::~Triangle ()
{}

double Triangle::collisionDate (const Ray &ray)
{
    const Vect AB = m_B - m_A;
    const Vect AC = m_C - m_A;
    const Vect PA = m_A - ray.pos();

    const Vect n = AB ^ AC;

    const double lambda = (n * PA) / (n * ray.dir());

    const Vect M = ray.pos() + lambda * ray.dir();

    // Check if M is in ABC
    if ( ((m_B-m_A) ^ (M-m_A)) * ((M-m_A) ^ (m_C-m_A)) >= -1e-12
      && ((m_A-m_B) ^ (M-m_B)) * ((M-m_B) ^ (m_C-m_B)) >= -1e-12
      && ((m_A-m_C) ^ (M-m_C)) * ((M-m_C) ^ (m_B-m_C)) >= -1e-12) {
        return lambda;
    }

    return INFINITY;
}

Color Triangle::color (const Ray &ray)
{
    const Vect intersection = ray.pos() + collisionDate(ray) * ray.dir();
    Vect normal = (m_B - m_A) ^ (m_C - m_A);
    normal.normalize();

    // TODO: use all lights
    Vect toLight = m_scene->lights()[0]->pos() - intersection;
    toLight.normalize();

    double dotProduct = normal * toLight;

    if (dotProduct < 0) {
        return Color(0, 0, 0);
    }

    return Color (dotProduct * m_material.color().red(),
                  dotProduct * m_material.color().green(),
                  dotProduct * m_material.color().blue());
}
