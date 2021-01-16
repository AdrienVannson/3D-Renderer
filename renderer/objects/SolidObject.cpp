#include "SolidObject.hpp"
#include "../Scene.hpp"

#include <algorithm>

SolidObject::SolidObject (const Material &material) :
    m_material (material)
{}

