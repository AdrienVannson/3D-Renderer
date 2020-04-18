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

bool Box::isEmtpy () const
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
