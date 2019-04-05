#ifndef VECT_HPP
#define VECT_HPP

#include <cmath>


class Vect
{
public:

    Vect (const double x=0, const double y=0, const double z=0);

    inline double x () const { return m_x; }
    inline void setX (const double x) { m_x = x; }

    inline double y () const { return m_y; }
    inline void setY (const double y) { m_y = y; }

    inline double z () const { return m_z; }
    inline void setZ (const double z) { m_z = z; }

    double norm () const;
    void normalize ();

protected:
    double m_x, m_y, m_z;
};

inline Vect operator+ (const Vect &a, const Vect &b) { return Vect(a.x()+b.x(), a.y()+b.y(), a.z()+b.z()); }
inline Vect operator- (const Vect &a, const Vect &b) { return Vect(a.x()-b.x(), a.y()-b.y(), a.z()-b.z()); }

inline Vect operator* (const double k, const Vect &v) { return Vect(k*v.x(), k*v.y(), k*v.z()); }
inline Vect operator* (const Vect &v, const double k) { return Vect(k*v.x(), k*v.y(), k*v.z()); }

inline double dist (const Vect &a, const Vect &b) { return Vect(a-b).norm(); }

#endif // VECT_HPP
