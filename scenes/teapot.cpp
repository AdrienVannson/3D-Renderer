#include "teapot.hpp"

#include "renderer/acceleration-structures/Octree.hpp"

Image* generateImageTeapot ()
{
    Scene *scene = new Scene;
    scene->setAccelerationStructure(new Octree);

    scene->load(":/resources/teapot.obj");

    scene->addLight(new Light(Vect(3, 2, 4)));

    scene->camera()->setPos( Vect (12, 12, 7.4) );
    scene->camera()->setDir( Vect (-3, -3, -1.5) );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
