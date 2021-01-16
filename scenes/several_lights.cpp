#include "several_lights.hpp"
#include "renderer/objects/Sphere.hpp"

Image* generateImageSeveralLights ()
{
    Scene *scene = new Scene;

    scene->load(":/resources/floor.obj", {
             Material(Color(100, 100, 100)),
             Material(Color(50, 50, 50))
    });

    scene->addObject(new Sphere(Vect(0, 0, 3), 2, Material(Color(255, 0, 0))));

    scene->addLight(new Light(Vect(0, 50, 150), 0.5));
    scene->addLight(new Light(Vect(0, -50, 150), 0.5));
    scene->camera()->setPos(Vect(30, 0, 6));

    Vect dir = -scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;
    scene->camera()->setDir( dir );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
