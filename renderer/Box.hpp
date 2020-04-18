#ifndef BOX_HPP
#define BOX_HPP

#include "Vect.hpp"


class Box
{
public:
    Box ();
    Box (const Vect minVertex, const Vect maxVertex);

    bool isEmtpy () const;

    Vect minVertex () const;
    Vect maxVertex () const;

    void reset ();

    void setMinVertex (const Vect vertex);
    void setMaxVertex (const Vect vertex);

    void addPoint (const Vect point);


private:
    Vect m_minVertex, m_maxVertex;
    bool m_isEmpty;
};

#endif // BOX_HPP
