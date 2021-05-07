#include "Stats.hpp"

long long Stats::m_rayTriangleIntersectionsCount = 0;
long long Stats::m_rayTriangleTestsCount = 0;
long long Stats::m_rayBoxIntersectionsCount = 0;
long long Stats::m_rayBoxTestsCount = 0;
clock_t Stats::m_startTime = 0;
clock_t Stats::m_endTime = 0;

void Stats::init ()
{
    m_rayTriangleTestsCount = 0;
    m_rayTriangleIntersectionsCount = 0;
    m_rayBoxIntersectionsCount = 0;
    m_rayBoxTestsCount = 0;

    m_startTime = clock();
}

void Stats::endTimer ()
{
    m_endTime = clock();
}

void Stats::print (std::ostream& os)
{
    const int width1 = 40;
    const int width2 = 16;

    os.imbue(std::locale("")); // Pretty print numbers
    os << "##### Statistics\n";

    os << std::left  << std::setw(width1) << "Total CPU time:"
       << std::right << std::setw(width2-2) << (double)(m_endTime-m_startTime) / CLOCKS_PER_SEC << " s\n";

    os << std::left  << std::setw(width1) << "Ray-triangle tests count:"
       << std::right << std::setw(width2) << rayTriangleTestsCount() << "\n";
    os << std::left  << std::setw(width1) << "Ray-triangle intersections count:"
       << std::right << std::setw(width2) << rayTriangleIntersectionsCount() << "\n";

    os << std::left  << std::setw(width1) << "Ray-box tests count:"
       << std::right << std::setw(width2) << rayBoxTestsCount() << "\n";
    os << std::left  << std::setw(width1) << "Ray-box intersections count:"
       << std::right << std::setw(width2) << rayBoxIntersectionsCount() << "\n";

    os.flush();
}
