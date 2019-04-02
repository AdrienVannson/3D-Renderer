#ifndef VECT_HPP
#define VECT_HPP


class Vect
{
public:

    Vect (const double x=0, const double y=0, const double z=0);

    inline double& x () { return m_x; }
    inline double& y () { return m_y; }
    inline double& z () { return m_z; }

    inline double x () const { return m_x; }
    inline double y () const { return m_y; }
    inline double z () const { return m_z; }

protected:
    double m_x, m_y, m_z;
};

#endif // VECT_HPP
