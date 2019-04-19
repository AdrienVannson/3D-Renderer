#include "Ray.hpp"

Ray::Ray (const Vect &pos, const Vect &dir) :
    m_pos (pos),
    m_dir (dir)
{}

void Ray::moveByEpsilon ()
{
    m_pos += 1e-12 * m_dir;
}
