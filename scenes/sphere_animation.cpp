#include "sphere_animation.hpp"
#include "image_utility.hpp"
#include "renderer/objects/Sphere.hpp"
#include "renderer/objects/implicit-objects/ImplicitObject.hpp"
#include "renderer/acceleration-structures/Octree.hpp"

#include <algorithm>
#include <vector>


// Sphere for the p-norm
class PSphere : public SolidObject
{
public:
    PSphere (Scene *scene, const double p) :
        SolidObject(scene),
        m_p (p)
    {}

    virtual ~PSphere () {};

    virtual double collisionDate (const Ray &ray) const
    {
        // Minimize the distance between O and the ray (trichotomy)
        double a = 0, b = Vect::dist(ray.pos(), Vect(0,0,0)) + 1;
        while (b-a > 1e-6) {
            const double x1 = 2./3. * a + 1./3. * b;
            const double x2 = 1./3. * a + 2./3. * b;

            if (distP(ray, x1) > distP(ray, x2)) {
                a = x1;
            }
            else {
                b = x2;
            }
        }

        // The ray and the sphere do not intersect
        if (distP(ray, b) > 1) return INFINITY;

        // Dichotomy to find where the ray and the sphere intersect
        a = 0;
        while (b-a > 1e-6) {
            const double m = (a + b) / 2;
            if (distP(ray, m) < 1) b = m;
            else a = m;
        }

        return b;
    }

    virtual Vect normal (const Vect &pos) const
    {
        Vect n(pow(abs(pos.x()), m_p) / pos.x(),
               pow(abs(pos.y()), m_p) / pos.y(),
               pow(abs(pos.z()), m_p) / pos.z());

        n.normalize();
        return n;
    }

    virtual Box boundingBox () const
    {
        return Box(Vect(-1, -1, -1), Vect(1, 1, 1));
    }

private:
    double distP (const Ray &ray, const double t) const
    {
        return distP(ray.pos() + t*ray.dir());
    }

    double distP (const Vect &pos) const
    {
        return pow(pow(abs(pos.x()), m_p)
                 + pow(abs(pos.y()), m_p)
                 + pow(abs(pos.z()), m_p), 1/m_p);
    }

    double m_p;
};

Image* generateImageSphere (const double p)
{
    Scene *scene = new Scene;
    scene->setBackgroundColor(Color(50, 50, 50));
    //scene->setAccelerationStructure(new Octree);

    PSphere *psphere = new PSphere (scene, p);
    psphere->setMaterial(Material(Color(255, 0, 0)));

    scene->addObject(psphere);

    scene->addLight(new Light(Vect(3, 2, 4)));

    scene->camera()->setHeight(800);
    scene->camera()->setWidth(800);

    scene->camera()->setPos( Vect(14, 14, 6.8) );
    scene->camera()->setDir( Vect(-3, -3, -1.5) );

    Image *image = scene->camera()->image();
    delete scene;
    return image;
}


void render ()
{
    std::vector<double> ps; // Values of p
    ps.push_back(1);
    ps.push_back(2);
    for (int p_int=101; p_int<=199; p_int+=2) {
        const double p = p_int / 100.;
        ps.push_back(p);
        ps.push_back(p / (p-1));
    }
    std::sort(ps.begin(), ps.end());

    for (int i=0; i<(int)ps.size(); i++) {
        const double p = ps[i];

        Image *image = generateImageSphere(p);

        std::string filename = std::to_string(i);
        filename = std::string(3 - filename.length(), '0') + filename + ".png";

        saveImage(*image, filename);
        //showImage(*image);
    }
}
