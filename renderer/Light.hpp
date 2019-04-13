#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vect.hpp"


class Light
{
public:
    Light (const Vect &pos=Vect());

    inline Vect pos () const { return m_pos; }
    inline void setPos (const Vect pos) { m_pos = pos; }

private:
    Vect m_pos;
};

#endif // LIGHT_HPP
