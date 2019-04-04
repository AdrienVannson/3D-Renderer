#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vect.hpp"

class Scene;


class Camera
{
public:
    Camera (Scene *scene, const int width=1280, const int height=720);

    inline int& width () { return m_width; }
    inline int width () const { return m_width; }

    inline int& height () { return m_height; }
    inline int height () const { return m_height; }

private:
    Vect m_pos; // Position of the focus point
    Vect m_dir;

    int m_width;
    int m_height;

    Scene *m_scene;
};

#endif // CAMERA_HPP
