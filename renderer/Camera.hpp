#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vect.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "Renderer.hpp"

class Scene;


class Camera
{
public:
    Camera (const int width=640, const int height=360);

    inline int width () const { return m_width; }
    inline void setWidth (const int width) { m_width = width; }

    inline int height () const { return m_height; }
    inline void setHeight (const int height) { m_height = height; }

    inline Vect pos () const { return m_pos; }
    inline void setPos (const Vect pos) { m_pos = pos; }

    inline Vect dir () const { return m_dir; }
    inline void setDir (const Vect dir) { m_dir = dir; }

    Image* image (Renderer *renderer) const;

private:
    Vect m_pos; // Position of the focus point
    Vect m_dir;

    int m_width;
    int m_height;
};

#endif // CAMERA_HPP
