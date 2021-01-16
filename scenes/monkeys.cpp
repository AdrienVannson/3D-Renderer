#include "monkeys.hpp"
#include "renderer/objects/Triangle.hpp"

Image* generateImageMonkeys ()
{
    Scene *scene = new Scene;

    scene->load(":/resources/monkey.obj");
    scene->addLight(new Light(Vect(3, 2, 4)));

    // Add mirror 1
    Vect a1 (20, -2, 0);
    Vect b1 (-10, -2, -10);
    Vect c1 (-10, -2, 10);
    scene->addObject(new Triangle(a1, b1, c1, Material(Color(0, 0, 0), 1)));

    // Add mirror 2
    Vect a2 (-2, 20, 0);
    Vect b2 (-2, -10, -10);
    Vect c2 (-2, -10, 10);
    scene->addObject(new Triangle(a2, b2, c2, Material(Color(0, 0, 0), 1)));

    scene->camera()->setPos(Vect(12, 12, 6.8));
    scene->camera()->setDir(Vect(-3, -3, -1.5));

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}
