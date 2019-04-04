#ifndef COLOR_HPP
#define COLOR_HPP


class Color
{
public:

    Color (const int red=0, const int green=0, const int blue=0);

    inline int& red () { return m_red; }
    inline int red () const { return m_red; }

    inline int& green () { return m_green; }
    inline int green () const { return m_green; }

    inline int& blue () { return m_blue; }
    inline int blue () const { return m_blue; }


private:
    int m_red, m_green, m_blue;
};

#endif // COLOR_HPP
