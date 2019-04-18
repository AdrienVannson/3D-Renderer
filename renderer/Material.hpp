#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"


class Material
{
public:
    Material (const Color &color=Color());
    Material (const bool isMirror);

    inline Color color () const { return m_color; }
    inline void setColor (const Color &color) { m_color = color; }

    inline bool isMirror () const { return m_isMirror; }
    inline void setIsMirror (const bool isMirror) { m_isMirror = isMirror; }

private:
    Color m_color;
    bool m_isMirror;
};

#endif // MATERIAL_HPP
