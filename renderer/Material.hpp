#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"


class Material
{
public:
    Material (const Color &color=Color());

    inline Color color () const { return m_color; }
    inline void setColor (const Color &color) { m_color = color; }

private:
    Color m_color;
};

#endif // MATERIAL_HPP
