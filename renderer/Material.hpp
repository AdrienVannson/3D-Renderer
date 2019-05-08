#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"


class Material
{
public:
    Material (const Color &color=Color(), const double reflectionCoef=0);

    inline Color color () const { return m_color; }
    inline void setColor (const Color &color) { m_color = color; }

    inline double reflectionCoef () const { return m_reflectionCoef; }
    inline void setReflectionCoef (const double reflectionCoef) { m_reflectionCoef = reflectionCoef; }

    inline double refractionCoef () const { return m_refractionCoef; }
    inline void setRefractionCoef (const double refractionCoef) { m_refractionCoef = refractionCoef; }

    inline double refractiveIndex () const { return m_refractiveIndex; }
    inline void setRefractiveIndex (const double refractiveIndex) { m_refractiveIndex = refractiveIndex; }

private:
    Color m_color;
    double m_reflectionCoef;
    double m_refractionCoef;

    double m_refractiveIndex;
};

#endif // MATERIAL_HPP
