#ifndef RAY_HPP
#define RAY_HPP

#include "Vect.hpp"


class Ray
{
public:
    Ray (const Vect &pos=Vect(), const Vect &dir=Vect());

    inline Vect pos () const
    {
        return m_pos;
    }

    inline void setPos (const Vect pos)
    {
        m_pos = pos;
    }

    inline Vect dir () const
    {
        return m_dir;
    }

    inline void setDir (const Vect dir)
    {
        m_dir = dir;
        m_dir.normalize();
    }

    void moveByEpsilon ();


private:
    Vect m_pos;
    Vect m_dir;
};

#endif // RAY_HPP
