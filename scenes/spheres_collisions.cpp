#include "spheres_collisions.hpp"
#include "image_utility.hpp"
#include "renderer/Scene.hpp"
#include "renderer/objects/Sphere.hpp"
#include "renderer/objects/Parallelogram.hpp"

struct DynamicSphere
{
    DynamicSphere(Sphere *sphere) :
        m_sphere(sphere),
        m_mass(1)
    {}
    ~DynamicSphere() {};

    Sphere *m_sphere;
    Vect m_velocity;
    double m_mass;
};

Scene *scene;
std::vector<DynamicSphere> spheres;

void moveSpheres(const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_sphere->setCenter(s.m_sphere->center() + t * s.m_velocity);
    }
}

void updateVelocities(const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_velocity.setZ(s.m_velocity.z() - t*9.81);
    }
}

void nextFrame(const double duration)
{
    for (int i=0; i<100; i++) {
        updateVelocities(duration/100);
        moveSpheres(duration/100);
    }
}


void renderSpheresCollision()
{
    scene = new Scene;
    scene->setBackgroundColor(Color(50, 50, 50));

    scene->addLight(new Light(Vect(3, 2, 4)));

    scene->camera()->setPos(2.5*Vect(14, 14, 6.8));
    scene->camera()->setDir(Vect(-3, -3, -1.5));

    // Sol
    double l = 10;
    Parallelogram *sol = new Parallelogram(scene, Vect(-l,-l), Vect(l,-l), Vect(-l,l), Material(Color(255,255,255)));
    scene->addObject(sol);

    // Spheres
    Sphere *sphere = new Sphere(scene, Vect(-5,0,2), 1, Material(Color(255,0,0)));
    scene->addObject(sphere);
    spheres.push_back(DynamicSphere(sphere));

    // Simulation
    for (int i=0; i<32; i++) {
        Image *image = scene->camera()->image();

        std::string filename = std::to_string(i);
        filename = std::string(3 - filename.length(), '0') + filename + ".png";

        saveImage(*image, filename);
        //showImage(*image);

        nextFrame(1. / 32.); // 32 fps
    }
}
