#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include "Color.hpp"


class Image
{
public:
    Image (const int width, const int height);

    int width () const;
    int height () const;

    Color color (const int x, const int y) const;
    void setColor (const int x, const int y, const Color color);

private:
    int m_width, m_height;
    std::vector<std::vector<Color>> m_pixels;
};

#endif // IMAGE_HPP
