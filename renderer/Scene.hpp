#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Vect.hpp"


class Scene
{
public:
    Scene ();
    ~Scene ();

    inline Camera* camera () { return m_camera; }


private:
    Camera *m_camera;
};

#endif // SCENE_HPP
