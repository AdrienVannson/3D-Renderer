#include "Color.hpp"

#include <algorithm>
using namespace std;

Color::Color (const int red, const int green, const int blue) :
    m_red (red),
    m_green (green),
    m_blue (blue)
{}

int Color::hex () const
{
    return 256*256*m_red + 256*m_green + m_blue;
}

void Color::operator+= (const Color &other)
{
    m_red = min(m_red + other.m_red, 255);
    m_green = min(m_green + other.m_green, 255);
    m_blue = min(m_blue + other.m_blue, 255);
}

void Color::operator*= (const double x)
{
    m_red *= x;
    m_green *= x;
    m_blue *= x;
}
