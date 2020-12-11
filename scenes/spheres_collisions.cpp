#include "spheres_collisions.hpp"
#include "image_utility.hpp"
#include "renderer/Scene.hpp"
#include "renderer/objects/Sphere.hpp"
#include "renderer/objects/Parallelogram.hpp"

#include <iostream>

struct DynamicSphere
{
    DynamicSphere (Sphere *sphere, const Vect velocity) :
        m_sphere(sphere),
        m_velocity(velocity),
        m_mass(1)
    {}
    ~DynamicSphere () {};

    Sphere *m_sphere;
    Vect m_velocity;
    double m_mass;
};

struct Collision
{
    Collision (DynamicSphere *s1, DynamicSphere *s2, const double date) :
        m_date(date),
        m_s1(s1),
        m_s2(s2)
    {}

    double m_date; // Time remaining before the collision happens
    DynamicSphere *m_s1, *m_s2; // If m_s2 = 0: collision with the floor
};

Scene *scene;
std::vector<DynamicSphere> spheres;

void moveSpheres (const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_sphere->setCenter(s.m_sphere->center() + t * s.m_velocity);
    }
}

void updateVelocities (const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_velocity.setZ(s.m_velocity.z() - t*9.81);
    }
}

std::vector<Collision> generateCollisions ()
{
    std::vector<Collision> collisions;

    // Collisions with the floor
    for (DynamicSphere &s : spheres) {
        const double z = s.m_sphere->center().z() - s.m_sphere->radius();

        if (z > 0 && s.m_velocity.z() < -1e-3) {
            collisions.push_back(Collision(&s, 0, -z / s.m_velocity.z()));
        }
    }

    return collisions;
}

Collision nextCollision ()
{
    Collision next(0, 0, INFINITY);

    for (Collision &c : generateCollisions()) {
        if (c.m_date < next.m_date) {
            next = c;
        }
    }

    return next;
}

void applyCollision (const Collision &c)
{
    if (c.m_s2 == 0) { // Collision with the floor
        c.m_s1->m_velocity.setZ(-c.m_s1->m_velocity.z());
    }
}

void nextFrame (double duration)
{
    const double stepMax = duration / 100.;

    while (duration > 1e-4) {
        double step = std::min(stepMax, duration);

        const Collision c = nextCollision();

        if (c.m_date > step) {
            moveSpheres(step);
            updateVelocities(step);
            duration -= step;
        }
        else {
            moveSpheres(c.m_date);
            applyCollision(c);
            updateVelocities(c.m_date);

            duration -= c.m_date;
        }
    }
}


void renderSpheresCollision ()
{
    scene = new Scene;
    scene->setBackgroundColor(Color(50, 50, 50));

    scene->addLight(new Light(2*Vect(3, 2, 4)));

    /*scene->camera()->setWidth(1920);
    scene->camera()->setHeight(1080);*/

    scene->camera()->setPos(2.5*Vect(14, 14, 6.8));
    scene->camera()->setDir(Vect(-3, -3, -1.5));

    // Sol
    double l = 10;
    Parallelogram *sol = new Parallelogram(scene, Vect(-l,-l), Vect(l,-l), Vect(-l,l), Material(Color(255,255,255)));
    scene->addObject(sol);

    // Spheres
    Sphere *sphere = new Sphere(scene, Vect(-6,0,4), 1, Material(Color(255,0,0)));
    scene->addObject(sphere);
    spheres.push_back(DynamicSphere(sphere, Vect(2,0,0)));

    // Simulation
    for (int i=0; i<8*32; i++) {
        Image *image = scene->camera()->image();

        std::string filename = std::to_string(i);
        filename = "output/" + std::string(3 - filename.length(), '0') + filename + ".png";

        saveImage(*image, filename);
        //showImage(*image);

        nextFrame(1. / 32.); // 32 fps
    }

    exit(0);
}
