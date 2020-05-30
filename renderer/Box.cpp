#include <algorithm>

#include "Box.hpp"
#include "objects/Parallelogram.hpp"
#include "Stats.hpp"

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

double getCollisitionDateParallelogram (const Ray &ray, const Vect A, const Vect B, const Vect C)
{
    const Vect n = (B-A) ^ (C-A);

    const double lambda = (n * (A - ray.pos())) / (n * ray.dir());

    if (lambda <= 0) {
        return INFINITY;
    }

    const Vect M = ray.pos() + lambda * ray.dir();
    const Vect D = B + C - A;

    // Check if M is in the parallelogram
    if ( ((B-A) ^ (M-B)) * ((B-A) ^ (C-B)) >= 0
      && ((C-A) ^ (M-C)) * ((C-A) ^ (B-C)) >= 0
      && ((B-D) ^ (M-B)) * ((B-D) ^ (C-B)) >= 0
      && ((C-D) ^ (M-C)) * ((C-D) ^ (B-C)) >= 0) {
        return lambda;
    }

    return INFINITY;
}

double Box::collisionDate (const Ray &ray) const
{
    Stats::addRayBoxTest();

    // If the ray starts inside the box
    if (ray.pos().x() >= m_minVertex.x() && ray.pos().x() <= m_maxVertex.x()
     && ray.pos().y() >= m_minVertex.y() && ray.pos().y() <= m_maxVertex.y()
     && ray.pos().z() >= m_minVertex.z() && ray.pos().z() <= m_maxVertex.z()) {
        Stats::addRayBoxIntersection();
        return 0;
    }

    double date = INFINITY;

    const Vect t = m_maxVertex - m_minVertex;

    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex,
            m_minVertex + Vect(t.x(), 0, 0),
            m_minVertex + Vect(0, t.y(), 0)
    ));
    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex,
            m_minVertex + Vect(t.x(), 0, 0),
            m_minVertex + Vect(0, 0, t.z())
    ));
    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex,
            m_minVertex + Vect(0, t.y(), 0),
            m_minVertex + Vect(0, 0, t.z())
    ));
    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex + Vect(0, t.y(), 0),
            m_minVertex + Vect(t.x(), t.y(), 0),
            m_minVertex + Vect(0, t.y(), t.z())
    ));
    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex + Vect(0, 0, t.z()),
            m_minVertex + Vect(t.x(), 0, t.z()),
            m_minVertex + Vect(0, t.y(), t.z())
    ));
    date = std::min(date, getCollisitionDateParallelogram(ray,
            m_minVertex + Vect(t.x(), 0, 0),
            m_minVertex + Vect(t.x(), t.y(), 0),
            m_minVertex + Vect(t.x(), 0, t.z())
    ));

    if (date != INFINITY) {
        Stats::addRayBoxIntersection();
    }

    return date;
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
