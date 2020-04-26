#include <algorithm>

#include "Box.hpp"

Box::Box () :
    m_minVertex (),
    m_maxVertex (),
    m_isEmpty (true)
{}

Box::Box (const Vect minVertex, const Vect maxVertex) :
    m_minVertex (minVertex),
    m_maxVertex (maxVertex),
    m_isEmpty (false)
{}

bool Box::isEmpty () const
{
    return m_isEmpty;
}

Vect Box::minVertex () const
{
    return m_minVertex;
}

Vect Box::maxVertex () const
{
    return m_maxVertex;
}

void Box::reset ()
{
    m_minVertex = Vect ();
    m_maxVertex = Vect ();
    m_isEmpty = true;
}

void Box::setMinVertex (const Vect vertex)
{
    m_minVertex = vertex;
    m_isEmpty = false;
}

void Box::setMaxVertex (const Vect vertex)
{
    m_maxVertex = vertex;
    m_isEmpty = false;
}

void Box::addPoint (const Vect point)
{
    if (m_isEmpty) {
        m_minVertex = point;
        m_maxVertex = point;
        m_isEmpty = false;
    }
    else {
        for (int i=0; i<3; i++) {
            m_minVertex[i] = std::min(m_minVertex[i], point[i]);
            m_maxVertex[i] = std::max(m_maxVertex[i], point[i]);
        }
    }
}

Box operator+ (const Box &a, const Box &b)
{
    if (a.m_isEmpty) return b;
    if (b.m_isEmpty) return a;

    Vect minVertex, maxVertex;

    for (int i=0; i<3; i++) {
        minVertex[i] = std::min(a.m_minVertex[i], b.m_minVertex[i]);
        maxVertex[i] = std::max(a.m_maxVertex[i], b.m_maxVertex[i]);
    }

    return Box (minVertex, maxVertex);
}

Box operator* (const Box &a, const Box &b)
{
    if (a.m_isEmpty || b.m_isEmpty) return Box ();

    Vect minVertex, maxVertex;

    for (int i=0; i<3; i++) {
        minVertex[i] = std::max(a.m_minVertex[i], b.m_minVertex[i]);
        maxVertex[i] = std::min(a.m_maxVertex[i], b.m_maxVertex[i]);

        if (maxVertex[i] < minVertex[i]) return Box ();
    }

    return Box(minVertex, maxVertex);
}
