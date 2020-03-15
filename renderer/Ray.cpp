#include "Ray.hpp"

Ray::Ray (const Vect &pos, const Vect &dir) :
    m_pos (pos),
    m_dir (dir)
{
    m_dir.normalize();
}

void Ray::moveByEpsilon ()
{
    m_pos += 1e-5 * m_dir;
}
