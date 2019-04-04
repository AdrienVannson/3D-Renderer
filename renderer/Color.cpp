#include "Color.hpp"

Color::Color (const int red, const int green, const int blue) :
    m_red (red),
    m_green (green),
    m_blue (blue)
{}

int Color::hex () const
{
    return 256*256*m_red + 256*m_green + m_blue;
}
