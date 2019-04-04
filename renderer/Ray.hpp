#ifndef RAY_HPP
#define RAY_HPP

#include "Vect.hpp"


class Ray
{
public:
    Ray (const Vect &pos=Vect(), const Vect &dir=Vect());

    inline Vect& pos () { return m_pos; }
    inline Vect pos () const { return m_pos; }

    inline Vect& dir () { return m_dir; }
    inline Vect dir () const { return m_dir; }


private:
    Vect m_pos;
    Vect m_dir;
};

#endif // RAY_HPP
