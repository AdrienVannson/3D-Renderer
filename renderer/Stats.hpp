#ifndef STATS_HPP
#define STATS_HPP

class Stats
{
public:
    static void init ();

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

private:
    static long long m_rayTriangleIntersectionsCount;
    static long long m_rayTriangleTestsCount;
    static long long m_rayBoxIntersectionsCount;
    static long long m_rayBoxTestsCount;
};

#endif // STATS_HPP
