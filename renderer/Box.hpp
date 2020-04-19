#ifndef BOX_HPP
#define BOX_HPP

#include "Vect.hpp"


class Box
{
public:
    Box ();
    Box (const Vect minVertex, const Vect maxVertex);

    bool isEmpty () const;

    Vect minVertex () const;
    Vect maxVertex () const;

    void reset ();

    void setMinVertex (const Vect vertex);
    void setMaxVertex (const Vect vertex);

    void addPoint (const Vect point);

    friend Box operator+ (const Box &a, const Box &b);
    friend Box operator* (const Box &a, const Box &b);

private:
    Vect m_minVertex, m_maxVertex;
    bool m_isEmpty;
};

Box operator+ (const Box &a, const Box &b); // Union
Box operator* (const Box &a, const Box &b); // Intersection


#endif // BOX_HPP
