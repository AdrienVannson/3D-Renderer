#include "Stats.hpp"

long long Stats::m_rayTriangleIntersectionsCount = 0;
long long Stats::m_rayTriangleTestsCount = 0;
long long Stats::m_rayBoxIntersectionsCount = 0;
long long Stats::m_rayBoxTestsCount = 0;

void Stats::init ()
{
    m_rayTriangleTestsCount = 0;
    m_rayTriangleIntersectionsCount = 0;
    m_rayBoxIntersectionsCount = 0;
    m_rayBoxTestsCount = 0;
}
