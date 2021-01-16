#include "Triangle.hpp"
#include "renderer/Stats.hpp"

Triangle::Triangle (const Vect &A, const Vect &B, const Vect &C, const Material &material) :
    SolidObject(material),
    m_A(A),
    m_B(B),
    m_C(C)
{}

Triangle::~Triangle ()
{}

double Triangle::collisionDate (const Ray &ray) const
{
    Stats::addRayTriangleTest();

    const Vect n = (m_B - m_A) ^ (m_C - m_A);

    const double lambda = (n * (m_A - ray.pos())) / (n * ray.dir());

    if (lambda <= 0) {
        return INFINITY;
    }

    const Vect M = ray.pos() + lambda * ray.dir();

    // Check if M is in ABC
    if ( ((m_B-m_A) ^ (M-m_A)) * ((M-m_A) ^ (m_C-m_A)) >= 0
      && ((m_A-m_B) ^ (M-m_B)) * ((M-m_B) ^ (m_C-m_B)) >= 0
      && ((m_A-m_C) ^ (M-m_C)) * ((M-m_C) ^ (m_B-m_C)) >= 0) {
        Stats::addRayTriangleIntersection();
        return lambda;
    }

    return INFINITY;
}

Vect Triangle::normal (const Vect &pos) const
{
    (void)pos;
    Vect normal = (m_B - m_A) ^ (m_C - m_A);
    normal.normalize();
    return normal;
}

Object::Collision Triangle::collision (const Ray &ray) const
{
    Collision col;
    col.date = collisionDate(ray);
    col.normal = normal(ray.pos() + col.date*ray.dir());
    col.material = m_material;
    return col;
}

Box Triangle::boundingBox () const
{
    Box res;
    res.addPoint(m_A);
    res.addPoint(m_B);
    res.addPoint(m_C);
    return res;
}
