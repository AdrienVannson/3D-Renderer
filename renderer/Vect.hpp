#ifndef VECT_HPP
#define VECT_HPP


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

protected:
    double m_x, m_y, m_z;
};

#endif // VECT_HPP
