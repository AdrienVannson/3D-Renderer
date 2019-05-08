#include "Material.hpp"

Material::Material (const Color &color, const double reflectionCoef) :
    m_color (color),
    m_reflectionCoef (reflectionCoef),
    m_refractionCoef (0),
    m_refractiveIndex (1)
{}
