#ifndef COLOR_HPP
#define COLOR_HPP


class Color
{
public:

    Color (const int red=0, const int green=0, const int blue=0);

    inline int red () const { return m_red; }
    inline void setRed (const int red) { m_red = red; }

    inline int green () const { return m_green; }
    inline void setGreen (const int green) { m_green = green; }

    inline int blue () const { return m_blue; }
    inline void setBlue (const int blue) { m_blue = blue; }

    int hex () const;


private:
    int m_red, m_green, m_blue;
};

#endif // COLOR_HPP
