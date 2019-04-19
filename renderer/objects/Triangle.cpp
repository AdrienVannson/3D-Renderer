#include "Triangle.hpp"
#include "../Scene.hpp"

Triangle::Triangle (Scene *scene, const Vect &A, const Vect &B, const Vect &C, const Material &material) :
    SolidObject (scene, material),

    m_A (A),
    m_B (B),
    m_C (C)
{}

Triangle::~Triangle ()
{}

double Triangle::collisionDate (const Ray &ray) const
{
    const Vect AB = m_B - m_A;
    const Vect AC = m_C - m_A;
    const Vect PA = m_A - ray.pos();

    const Vect n = AB ^ AC;

    const double lambda = (n * PA) / (n * ray.dir());

    if (lambda <= 0) {
        return INFINITY;
    }

    const Vect M = ray.pos() + lambda * ray.dir();

    // Check if M is in ABC
    if ( ((m_B-m_A) ^ (M-m_A)) * ((M-m_A) ^ (m_C-m_A)) >= -1e-9
      && ((m_A-m_B) ^ (M-m_B)) * ((M-m_B) ^ (m_C-m_B)) >= -1e-9
      && ((m_A-m_C) ^ (M-m_C)) * ((M-m_C) ^ (m_B-m_C)) >= -1e-9) {
        return lambda;
    }

    return INFINITY;
}

Vect Triangle::normal (const Vect &pos) const
{
    Vect normal = (m_B - m_A) ^ (m_C - m_A);
    normal.normalize();
    return normal;
}
