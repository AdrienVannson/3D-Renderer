#include "Parallelogram.hpp"

Parallelogram::Parallelogram (Scene *scene, const Vect &A, const Vect &B, const Vect &C, const Material &material) :
    SolidObject (scene, material),
    m_A (A),
    m_B (B),
    m_C (C)
{}

Parallelogram::~Parallelogram ()
{}

double Parallelogram::collisionDate (const Ray &ray) const
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

    // Check if M is in the other part of the parallelogram
    const Vect opA = m_B + m_C - m_A;
    if ( ((m_B-opA) ^ (M-opA)) * ((M-opA) ^ (m_C-opA)) >= -1e-9
      && ((opA-m_B) ^ (M-m_B)) * ((M-m_B) ^ (m_C-m_B)) >= -1e-9
      && ((opA-m_C) ^ (M-m_C)) * ((M-m_C) ^ (m_B-m_C)) >= -1e-9) {
        return lambda;
    }

    return INFINITY;
}

Vect Parallelogram::normal (const Vect &pos) const
{
    (void)pos;
    Vect normal = (m_B - m_A) ^ (m_C - m_A);
    normal.normalize();
    return normal;
}

Box Parallelogram::boundingBox () const
{
    Box res;
    res.addPoint(m_A);
    res.addPoint(m_B);
    res.addPoint(m_C);
    return res;
}
