#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vect.hpp"


class Light
{
public:
    Light (const Vect &pos=Vect(), const double intensity=1);

    inline Vect pos () const { return m_pos; }
    inline void setPos (const Vect pos) { m_pos = pos; }

    inline double intensity () const { return m_intensity; }
    inline void setIntensity (const double intensity) { m_intensity = intensity; }

private:
    Vect m_pos;
    double m_intensity;
};

#endif // LIGHT_HPP
