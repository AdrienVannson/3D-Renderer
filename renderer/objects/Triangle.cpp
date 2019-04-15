#include "Triangle.hpp"

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
    return INFINITY;
}

Color Triangle::color (const Ray &ray)
{
    return Color ();
}

