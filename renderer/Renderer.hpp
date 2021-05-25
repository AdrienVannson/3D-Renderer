#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Color.hpp"
#include "Ray.hpp"
class Scene;

/// \brief Computes the color of a ray
class Renderer
{
public:
    Renderer(Scene *scene);
    virtual ~Renderer();

    virtual Color color(const Ray &ray, const int remainingDepth);

protected:
    Scene *m_scene;
};

#endif // RENDERER_HPP
