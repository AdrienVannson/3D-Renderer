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
    CollisionWall (DynamicSphere *s, const int c, const double date) :
        Collision(date),
        m_s(s),
        m_c(c)
    {}
    virtual ~CollisionWall () {}

    virtual void apply () override
    {
        const double a = (*m_s).m_velocity[m_c];

        (*m_s).m_velocity[m_c] *= -1;

        if (-a != (*m_s).m_velocity[m_c]) {
            std::cerr << a << " " << (*m_s).m_velocity[m_c] << std::endl;
            exit(0);
        }
    }

private:
    DynamicSphere *m_s;
    int m_c;
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

        if (s.m_velocity.z() < -1e-3) {
            const double z = s.m_sphere->center().z() - s.m_sphere->radius();

            double date = -z / s.m_velocity.z();

            if (!next || date < next->m_date) {
                delete next;
                next = new CollisionWall(&s, 2, date);
            }
        }

        if (abs(s.m_velocity.x()) > 1e-3) {
            const double d = s.m_velocity.x() > 0 ? 7-s.m_sphere->center().x()-s.m_sphere->radius()
                                                  : 7+s.m_sphere->center().x()-s.m_sphere->radius();
            double date = abs(d / s.m_velocity.x());

            if (!next || date < next->m_date) {
                delete next;
                next = new CollisionWall(&s, 0, date);
            }
        }

        if (abs(s.m_velocity.y()) > 1e-3) {
            const double d = s.m_velocity.y() > 0 ? 7-s.m_sphere->center().y()-s.m_sphere->radius()
                                                  : 7+s.m_sphere->center().y()-s.m_sphere->radius();
            double date = abs(d / s.m_velocity.y());

            if (!next || date < next->m_date) {
                delete next;
                next = new CollisionWall(&s, 1, date);
            }
        }
    }

    // Collisions between spheres
    for (int i=0; i<(int)spheres.size(); i++) {
        for (int j=i+1; j<(int)spheres.size(); j++) {
            DynamicSphere &s1 = spheres[i];
            DynamicSphere &s2 = spheres[j];
            const double r = s1.m_sphere->radius() + s2.m_sphere->radius();

            const double x = s2.m_sphere->center().x() - s1.m_sphere->center().x();
            const double y = s2.m_sphere->center().y() - s1.m_sphere->center().y();
            const double z = s2.m_sphere->center().z() - s1.m_sphere->center().z();

            const double vx = s2.m_velocity.x() - s1.m_velocity.x();
            const double vy = s2.m_velocity.y() - s1.m_velocity.y();
            const double vz = s2.m_velocity.z() - s1.m_velocity.z();

            const double a = vx*vx + vy*vy + vz*vz;
            const double b = x*vx + y*vy + z*vz;
            const double c = x*x + y*y + z*z - r*r;

            const double delta = b*b - a*c;

            if (a > 1e-4 && delta > 1e-4) {
                const double date = (-b - std::sqrt(delta)) / a;

                if (date >= 0 && (!next || date < next->m_date)) {
                    delete next;
                    next = new CollisionSphere(&s1, &s2, date);
                }
            }
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

    scene->addLight(new Light(Vect(4, 3, 20), 1));

#if 1
    scene->camera()->setWidth(1920);
    scene->camera()->setHeight(1080);
#endif

    scene->camera()->setPos(2.5*Vect(14, 14, 6.8));
    scene->camera()->setDir(Vect(-3, -3, -1.5));

    // Floor
    double l = 10;
    double d = 7;
    Parallelogram *floor = new Parallelogram(scene, Vect(-l,-l), Vect(l,-l), Vect(-l,l),
                                             Material(Color(244,143,177), 0.07));
    scene->addObject(floor);

    // Walls
    Parallelogram *wall1 = new Parallelogram(scene, Vect(-l,-d), Vect(-l,-d,5), Vect(l,-d),
                                             Material(Color(244,143,177), 0.07));
    scene->addObject(wall1);

    Parallelogram *wall2 = new Parallelogram(scene, Vect(-d,-l), Vect(-d,l), Vect(-d,-l,5),
                                             Material(Color(244,143,177), 0.07));
    scene->addObject(wall2);

    // Spheres
    for (int x=-5; x<=5; x+=5) {
        for (int y=-5; y<=5; y+=5) {
            const double c1 = 50 + rand() % 200;
            const double c2 = 50 + rand() % 200;
            const double c3 = 50 + rand() % 200;

            Sphere *sphere = new Sphere(scene, Vect(x,y,4), 1, Material(Color(c1,c2,c3), 0.12));
            scene->addObject(sphere);

            const double vx = (rand() % 200) / 100. - 1;
            const double vy = (rand() % 200) / 100. - 1;
            const double vz = (rand() % 200) / 100. - 1;

            spheres.push_back(DynamicSphere(sphere, Vect(vx, vy, vz)));
        }
    }

    // Simulation
    for (int i=0; i<60*60; i++) { // 60s, 60fps
        const int process = 0; // Update to render different parts of the animation

        if ( (process == 0 && i < 15*60)
          || (process == 1 && i >= 15*60 && i < 30*60)
          || (process == 2 && i >= 30*60 && i < 45*60)
          || (process == 3 && i >= 45*60) ) {
            Image *image = scene->camera()->image();

            std::string filename = std::to_string(i);
            filename = "output" + std::to_string(process) + "/"
                     + std::string(4 - filename.length(), '0') + filename + ".png";

            saveImage(*image, filename);
            //showImage(*image);

            delete image;
        }

        nextFrame(1. / 60.); // 60 fps
    }

    exit(0);

    // To create a video:
    // ffmpeg -framerate 60 -i %04d.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
}
