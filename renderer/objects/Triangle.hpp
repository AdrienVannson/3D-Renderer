#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"
#include "../Material.hpp"


class Triangle : public Object
{
public:
    Triangle (Scene *scene, const Vect &A=Vect(), const Vect &B=Vect(), const Vect &C=Vect(), const Material &material=Material());
    virtual ~Triangle ();

    inline Vect A () const { return m_A; }
    inline void setA (const Vect &A) { m_A = A; }

    inline Vect B () const { return m_B; }
    inline void setB (const Vect &B) { m_B = B; }

    inline Vect C () const { return m_C; }
    inline void setC (const Vect &C) { m_C = C; }

    inline Material material () const { return m_material; }
    inline void setMaterial (const Material &material) { m_material = material; }

    virtual double collisionDate (const Ray &ray);
    virtual Color color (const Ray &ray);

private:
    Vect m_A, m_B, m_C;

    Material m_material;
};

#endif // TRIANGLE_HPP
