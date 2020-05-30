#ifndef STATS_HPP
#define STATS_HPP

class Stats
{
public:
    static void init ();

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

private:
    static long long m_rayTriangleIntersectionsCount;
    static long long m_rayTriangleTestsCount;
};

#endif // STATS_HPP
