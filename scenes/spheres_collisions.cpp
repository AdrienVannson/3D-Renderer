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

class Collision
{
public:
    Collision (const double date) :
        m_date(date)
    {}
    virtual ~Collision () {}

    virtual void apply () = 0;

    double m_date; // Time remaining before the collision happens
};

class CollisionWall : public Collision
{
public:
    CollisionWall (DynamicSphere *s, const double date) :
        Collision(date),
        m_s(s)
    {}
    virtual ~CollisionWall () {}

    virtual void apply () override
    {
        m_s->m_velocity.setZ(-m_s->m_velocity.z());
    }

private:
    DynamicSphere *m_s;
};

class CollisionSphere : public Collision
{
public:
    CollisionSphere (DynamicSphere *s1, DynamicSphere *s2, const double date) :
        Collision(date),
        m_s1(s1),
        m_s2(s2)
    {}
    virtual ~CollisionSphere () {}

    virtual void apply () override
    {
        apply(m_s1, m_s2);
        apply(m_s2, m_s1);
    }

private:
    DynamicSphere *m_s1, *m_s2;

    static void apply (DynamicSphere *a, DynamicSphere *b)
    {
        Vect u = a->m_sphere->center() - b->m_sphere->center();
        u.normalize();

        b->m_velocity = b->m_velocity - 2.*(b->m_velocity * u)*u;
    }
};

Scene *scene;
std::vector<DynamicSphere> spheres;

void moveSpheres (const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_sphere->setCenter(s.m_sphere->center() + t*s.m_velocity);
    }
}

void updateVelocities (const double t) // t: duration
{
    for (DynamicSphere &s : spheres) {
        s.m_velocity.setZ(s.m_velocity.z() - t*9.81);
    }
}

Collision* nextCollision ()
{
    Collision *next = 0;

    // Collisions with the floor
    for (DynamicSphere &s : spheres) {
        const double z = s.m_sphere->center().z() - s.m_sphere->radius();

        if (s.m_velocity.z() >= -1e-3) continue;

        double time = -z / s.m_velocity.z();

        if (!next || time < next->m_date) {
            delete next;
            next = new CollisionWall(&s, time);
        }
    }

    return next;
}

void nextFrame (double duration)
{
    const double stepMax = duration / 100.;

    while (duration > 1e-4) {
        double step = std::min(stepMax, duration);

        Collision *c = nextCollision();

        if (!c || c->m_date > step) {
            moveSpheres(step);
            updateVelocities(step);
            duration -= step;
        }
        else {
            moveSpheres(std::max(c->m_date, 0.));
            c->apply();
            updateVelocities(std::max(c->m_date, 0.));

            duration -= std::max(c->m_date, 0.);
        }

        delete c;
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
    Sphere *sphere1 = new Sphere(scene, Vect(-6,0,4), 1, Material(Color(255,0,0)));
    scene->addObject(sphere1);
    spheres.push_back(DynamicSphere(sphere1, Vect(2,0,0)));

    Sphere *sphere2 = new Sphere(scene, Vect(6,0,3), 1, Material(Color(0,0,255)));
    scene->addObject(sphere2);
    spheres.push_back(DynamicSphere(sphere2, Vect(-2,0,0)));

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

    // To create a video:
    // ffmpeg -framerate 32 -i %03d.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
}
