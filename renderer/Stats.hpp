#ifndef STATS_HPP
#define STATS_HPP

#include <iomanip>
#include <ostream>

class Stats
{
public:
    static void init ();
    static void endTimer ();

    // Triangle
    static inline void addRayTriangleTest () {
        m_rayTriangleTestsCount++;
    }
    static inline long long rayTriangleTestsCount () {
        return m_rayTriangleTestsCount;
    }

    static inline void addRayTriangleIntersection () {
        m_rayTriangleIntersectionsCount++;
    }
    static inline long long rayTriangleIntersectionsCount () {
        return m_rayTriangleIntersectionsCount;
    }

    // Box
    static inline void addRayBoxTest () {
        m_rayBoxTestsCount++;
    }
    static inline long long rayBoxTestsCount () {
        return m_rayBoxTestsCount;
    }

    static inline void addRayBoxIntersection () {
        m_rayBoxIntersectionsCount++;
    }
    static inline long long rayBoxIntersectionsCount () {
        return m_rayBoxIntersectionsCount;
    }

    static void print (std::ostream&);

private:
    static long long m_rayTriangleIntersectionsCount;
    static long long m_rayTriangleTestsCount;
    static long long m_rayBoxIntersectionsCount;
    static long long m_rayBoxTestsCount;

    static clock_t m_startTime, m_endTime;
};

#endif // STATS_HPP
