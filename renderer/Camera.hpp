#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vect.hpp"


class Camera : public Vect
{
public:
    Camera (const int width=1280, const int height=720);

    inline int& width () { return m_width; }
    inline int width () const { return m_width; }

    inline int& height () { return m_height; }
    inline int height () const { return m_height; }

private:
    int m_width;
    int m_height;
};

#endif // CAMERA_HPP
