#include "sphere_mirror.hpp"
#include "renderer/objects/Sphere.hpp"

Image* generateImageSphereMirror ()
{
    Scene *scene = new Scene;

    scene->load(":/resources/checkerboard.obj", {
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0)),
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0)),
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0))
    });

    scene->addObject(new Sphere(Vect(8, 8, 4), 4, Material(Color(0, 0, 0), 1)));

    scene->addLight(new Light(5*Vect(8, 20, 12)));

    scene->camera()->setPos( 30*Vect(1, 1, 1) );

    Vect dir = -scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;

    scene->camera()->setDir( dir );
    scene->camera()->setWidth(1024);
    scene->camera()->setHeight(1024);

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
