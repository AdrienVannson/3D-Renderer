#include "Material.hpp"

Material::Material (const Color &color) :
    m_color (color),
    m_isMirror (false)
{}

Material::Material (const bool isMirror) :
    m_color (Color(0, 0, 0)),
    m_isMirror (isMirror)
{}
