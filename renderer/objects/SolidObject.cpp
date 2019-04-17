#include "SolidObject.hpp"

SolidObject::SolidObject (Scene *scene, const Material &material) :
    Object (scene),
    m_material (material)
{

}
