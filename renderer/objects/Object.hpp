#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../Ray.hpp"
#include "../Color.hpp"

class Scene;


class Object
{
public:
    Object (Scene *scene);
    virtual ~Object ();

    virtual double collisionDate (const Ray &ray) = 0;
    virtual Color color (const Ray &ray) = 0;

protected:
    Scene *m_scene;
};

#endif // OBJECT_HPP
