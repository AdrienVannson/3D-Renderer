#include "torus_knot.hpp"

Image* generateImageTorusKnot ()
{
    Scene *scene = new Scene;

    scene->load(":/resources/knot.obj");

    scene->addLight(new Light(Vect(3, 2, 4)));

    scene->camera()->setPos( Vect (14, 14, 6.8) );
    scene->camera()->setDir( Vect (-3, -3, -1.5) );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
