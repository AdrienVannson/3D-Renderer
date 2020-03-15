#include "Image.hpp"

using namespace std;

Image::Image (const int width, const int height) :
    m_width (width),
    m_height (height)
{
    m_pixels.resize(width);
    for (vector<Color> &column : m_pixels) {
        column.resize(height);
    }
}

int Image::width () const
{
    return m_width;
}

int Image::height () const
{
    return m_height;
}

Color Image::color (const int x, const int y) const
{
    return m_pixels[x][y];
}

void Image::setColor (const int x, const int y, const Color color)
{
    m_pixels[x][y] = color;
}
