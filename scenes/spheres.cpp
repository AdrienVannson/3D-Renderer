#include "spheres.hpp"
#include "renderer/objects/Sphere.hpp"

Image* generateImageSpheres ()
{
    Scene *scene = new Scene;

    scene->addObject(new Sphere (scene, Vect(-1, 0, 1), 1, Material(Color(255, 0, 0))));
    scene->addObject(new Sphere (scene, Vect(-1, -2.1, 1), 1, Material(Color(0, 255, 0)))); // Left
    scene->addObject(new Sphere (scene, Vect(-1, 2.1, 1), 1, Material(Color(0, 0, 255), 0.6))); // Right

    scene->addLight(new Light(Vect(3, 2, 2)));

    scene->camera()->setPos( Vect (10, 0, 1) );
    scene->camera()->setDir( Vect (-3, 0, 0) );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
