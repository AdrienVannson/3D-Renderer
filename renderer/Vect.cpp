#include "Vect.hpp"

Vect::Vect (const double x, const double y, const double z) :
    m_x (x),
    m_y (y),
    m_z (z)
{}

double Vect::norm () const
{
    return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

void Vect::normalize ()
{
    const double currentNorm = norm();

    m_x /= currentNorm;
    m_y /= currentNorm;
    m_z /= currentNorm;
}

Vect Vect::operator- () const
{
    return Vect (-m_x, -m_y, -m_z);
}

void Vect::operator*= (const double k)
{
    m_x *= k;
    m_y *= k;
    m_z *= k;
}

void Vect::operator/= (const double k)
{
    m_x /= k;
    m_y /= k;
    m_z /= k;
}

void Vect::operator+= (const Vect &v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
}

void Vect::operator-= (const Vect &v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
}
