#include "profile_picture.hpp"

Image* generateImageProfilePicture ()
{
    Scene *scene = new Scene;

    scene->load(":/resources/profile_picture.obj", {Material(Color(144, 214, 117)), Material(Color(255, 42, 24))});

    scene->setBackgroundColor(Color (39, 123, 255)); // Blue

    scene->addLight(new Light(Vect(5, -3, 6)));

    scene->camera()->setPos( Vect (7, -7, 1.75) );

    Vect dir = -scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;

    scene->camera()->setDir( dir );

    scene->camera()->setWidth(256);
    scene->camera()->setHeight(256);

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
