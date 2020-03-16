#include "sphere_refraction.hpp"
#include "renderer/objects/Sphere.hpp"

Image* generateImageSpheresRefraction ()
{
    Scene *scene = new Scene;

    scene->setBackgroundColor(Color(40, 120, 255));

    scene->load(":/resources/floor.obj", {
             Material(Color(255, 0, 0)),
             Material(Color(0, 0, 255))
    });

    Material material (Color(50, 50, 50));
    material.setRefractionCoef(0.8);
    material.setRefractiveIndex(1.3);

    scene->addObject(new Sphere (scene, Vect(5, 0, 1), 1, material));

    scene->addLight(new Light(Vect(6, 2, 5)));

    scene->camera()->setPos( Vect (17, -0.5, 5) );
    scene->camera()->setDir( Vect (-3, 0.1, -1) );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
