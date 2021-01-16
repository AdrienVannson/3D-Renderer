#include "Object.hpp"

Object::Object ()
{}

Object::~Object ()
{}

double Object::collisionDate (const Ray &ray) const
{
    return collision(ray).date;
}
