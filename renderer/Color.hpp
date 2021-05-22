#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
    Color ();
    Color (const int red, const int green, const int blue);
    Color (const int hex);

    inline int red () const { return m_red; }
    inline void setRed (const int red) { m_red = red; }

    inline int green () const { return m_green; }
    inline void setGreen (const int green) { m_green = green; }

    inline int blue () const { return m_blue; }
    inline void setBlue (const int blue) { m_blue = blue; }

    int hex () const;


    void operator+= (const Color &other);
    void operator*= (const double x);


private:
    int m_red, m_green, m_blue;
};

#endif // COLOR_HPP
