#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "Camera.hpp"
#include "Vect.hpp"
#include "Light.hpp"
#include "objects/Object.hpp"


class Scene
{
public:
    Scene ();
    ~Scene ();

    inline Camera* camera () { return m_camera; }

    inline const std::vector<Object*>& objects () const { return m_objects; }
    inline void addObject (Object *object) { m_objects.push_back(object); }

    inline const std::vector<Light*>& lights () const { return m_lights; }
    inline void addLight (Light *light) { m_lights.push_back(light); }


private:
    Camera *m_camera;

    std::vector<Object*> m_objects;
    std::vector<Light*> m_lights;
};

#endif // SCENE_HPP
