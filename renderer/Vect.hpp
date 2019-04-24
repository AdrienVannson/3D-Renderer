#ifndef VECT_HPP
#define VECT_HPP

#include <cmath>


class Vect
{
public:
    inline Vect (const double x=0, const double y=0, const double z=0) :
        m_x (x),
        m_y (y),
        m_z (z)
    {}

    inline double x () const { return m_x; }
    inline void setX (const double x) { m_x = x; }

    inline double y () const { return m_y; }
    inline void setY (const double y) { m_y = y; }

    inline double z () const { return m_z; }
    inline void setZ (const double z) { m_z = z; }

    inline double norm () const { return sqrt(m_x*m_x + m_y*m_y + m_z*m_z); };

    inline void normalize ()
    {
        const double currentNorm = norm();

        m_x /= currentNorm;
        m_y /= currentNorm;
        m_z /= currentNorm;
    }

    inline Vect operator- () const { return Vect (-m_x, -m_y, -m_z); };

    inline void operator*= (const double k) { m_x*=k; m_y*=k; m_z*=k; }
    inline void operator/= (const double k) { m_x /= k; m_y /= k; m_z /= k; }
    inline void operator+= (const Vect &v) { m_x += v.m_x; m_y += v.m_y; m_z += v.m_z; }
    inline void operator-= (const Vect &v) { m_x -= v.m_x; m_y -= v.m_y; m_z -= v.m_z; }

protected:
    double m_x, m_y, m_z;
};

inline Vect operator+ (const Vect &a, const Vect &b) { return Vect(a.x()+b.x(), a.y()+b.y(), a.z()+b.z()); }
inline Vect operator- (const Vect &a, const Vect &b) { return Vect(a.x()-b.x(), a.y()-b.y(), a.z()-b.z()); }

inline double operator* (const Vect &a, const Vect &b) // Dot product
{
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

inline Vect operator^ (const Vect &a, const Vect &b) // Cross product
{
    return Vect (a.y() * b.z() - b.y() * a.z(),
                 a.z() * b.x() - b.z() * a.x(),
                 a.x() * b.y() - b.x() * a.y());
}

inline Vect operator* (const double k, const Vect &v) { return Vect(k*v.x(), k*v.y(), k*v.z()); }
inline Vect operator* (const Vect &v, const double k) { return Vect(k*v.x(), k*v.y(), k*v.z()); }

inline double dist (const Vect &a, const Vect &b) { return Vect(a-b).norm(); }

#endif // VECT_HPP
