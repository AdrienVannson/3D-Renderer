#include "Parallelogram.hpp"

Parallelogram::Parallelogram (const Vect &A, const Vect &B, const Vect &C, const Material &material) :
    SolidObject(material),
    m_A(A),
    m_B(B),
    m_C(C)
{}

Parallelogram::~Parallelogram ()
{}

double Parallelogram::collisionDate (const Ray &ray) const
{
    const Vect n = (m_B - m_A) ^ (m_C - m_A);

    const double lambda = (n * (m_A - ray.pos())) / (n * ray.dir());

    if (lambda <= 0) {
        return INFINITY;
    }

    const Vect M = ray.pos() + lambda * ray.dir();
    const Vect D = m_B + m_C - m_A;

    // Check if M is in the parallelogram
    if ( ((m_B-m_A) ^ (M-m_B)) * ((m_B-m_A) ^ (m_C-m_B)) >= 0
      && ((m_C-m_A) ^ (M-m_C)) * ((m_C-m_A) ^ (m_B-m_C)) >= 0
      && ((m_B-D) ^ (M-m_B)) * ((m_B-D) ^ (m_C-m_B)) >= 0
      && ((m_C-D) ^ (M-m_C)) * ((m_C-D) ^ (m_B-m_C)) >= 0) {
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

Object::Collision Parallelogram::collision (const Ray &ray) const
{
    Collision col;
    col.date = collisionDate(ray);
    col.normal = normal(ray.pos() + col.date*ray.dir());
    col.material = m_material;
    return col;
}

Box Parallelogram::boundingBox () const
{
    Box res;
    res.addPoint(m_A);
    res.addPoint(m_B);
    res.addPoint(m_C);
    return res;
}
