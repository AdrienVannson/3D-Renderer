#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP

#include "SolidObject.hpp"


class Parallelogram : public SolidObject
{
public:
    Parallelogram (const Vect &A=Vect(), const Vect &B=Vect(), const Vect &C=Vect(),
                   const Material &material=Material());
    virtual ~Parallelogram ();

    inline Vect A () const { return m_A; }
    inline void setA (const Vect &A) { m_A = A; }

    inline Vect B () const { return m_B; }
    inline void setB (const Vect &B) { m_B = B; }

    inline Vect C () const { return m_C; }
    inline void setC (const Vect &C) { m_C = C; }

    double collisionDate (const Ray &ray) const;
    Vect normal (const Vect &pos) const;
    Collision collision (const Ray &ray) const override;

    virtual Box boundingBox () const override;

private:
    // The parallelogram is composed of 4 points: A, B, C and the point opposite A
    Vect m_A, m_B, m_C;
};

#endif // PARALLELOGRAM_HPP
