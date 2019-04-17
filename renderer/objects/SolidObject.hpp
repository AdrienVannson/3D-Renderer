#ifndef SOLIDOBJECT_HPP
#define SOLIDOBJECT_HPP

#include "Object.hpp"
#include "../Material.hpp"


class SolidObject : public Object
{
public:
    SolidObject (Scene *scene, const Material &material=Material());

    inline Material material () const { return m_material; }
    inline void setMaterial (const Material &material) { m_material = material; }

protected:
    Material m_material;
};

#endif // SOLIDOBJECT_HPP
