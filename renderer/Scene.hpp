#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <cmath>

#include "AccelerationStructure.hpp"
#include "Camera.hpp"
#include "Vect.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Material.hpp"
#include "objects/Group.hpp"

#include <QString>
#include <QFile>
#include <QTextStream>


class Scene
{
public:
    Scene ();
    ~Scene ();

    inline Camera* camera () { return m_camera; }

    inline AccelerationStructure* accelerationStructure ()
    {
        return m_accelerationStructure;
    }
    inline void setAccelerationStructure (AccelerationStructure *accelerationStructure)
    {
        delete m_accelerationStructure;
        m_accelerationStructure = accelerationStructure;
    }

    inline const std::vector<Object*>& objects () const { return m_objects; }
    inline void addObject (Object *object) { m_objects.push_back(object); }

    inline const std::vector<Light*>& lights () const { return m_lights; }
    inline void addLight (Light *light) { m_lights.push_back(light); }

    inline Color backgroundColor () const { return m_backgroundColor; }
    inline void setBackgroundColor (const Color &backgroundColor) { m_backgroundColor = backgroundColor; }

    void load (QString filename, const std::vector<Material> &materials={});

    // Rendering
    void initRender ();
    double collisionDate (const Ray &ray) const;
    Color color (const Ray &ray, const int remainingDepth) const;

private:
    AccelerationStructure *m_accelerationStructure;

    Camera *m_camera;

    std::vector<Object*> m_objects;
    std::vector<Light*> m_lights;

    Color m_backgroundColor;
};

#endif // SCENE_HPP
