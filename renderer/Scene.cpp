#include <sstream>

#include "Scene.hpp"
#include "objects/Triangle.hpp"
#include "renderer/acceleration-structures/SlowIntersection.hpp"

using namespace std;

Scene::Scene () :
    m_accelerationStructure (new SlowIntersection),
    m_backgroundColor (Color(80, 80, 80))
{
    m_camera = new Camera(this);
    m_root = new Group();
}

Scene::~Scene ()
{
    delete m_accelerationStructure;
    delete m_camera;
    delete m_root;

    for (Light *light : m_lights) {
        delete light;
    }
}


/*
 * Object loading
 */

void Scene::load (QString filename, const std::vector<Material> &materials)
{
    Group *group = new Group();

    int iObject = -1;
    vector<Vect> vertice;
    Material material;

    QFile file (filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream stream (&file);

    while (!stream.atEnd()) {
        const string line = stream.readLine().toStdString();
        stringstream stream;
        stream << line;

        if (line[1] == ' ') {
            if (line[0] == 'v') {
                char c;
                stream >> c;

                double x, y, z;
                stream >> x >> y >> z;

                vertice.push_back(Vect(x, y, z));
            }
            else if (line[0] == 'f') {
                char c;
                int i;
                stream >> c;

                int indexes[3];

                stream >> indexes[0];
                stream >> c >> c >> i;
                stream >> indexes[1];
                stream >> c >> c >> i;
                stream >> indexes[2];

                group->addObject(new Triangle(vertice[indexes[0]-1], vertice[indexes[1]-1], vertice[indexes[2]-1],
                                              material));
            }
            else if (line[0] == 'o') {
                iObject++;

                // Update material
                if (iObject < (int)materials.size()) {
                    material = materials[iObject];
                }
                else {
                    material = Material(Color(255, 0, 0));
                }
            }
        }
    }

    addObject(group);
}


/*
 * Rendering
 */

void Scene::initRender ()
{
    m_accelerationStructure->init(m_root);
}

double Scene::collisionDate (const Ray &ray) const
{
    Object *object = m_accelerationStructure->getObjectIntersecting(ray);
    return object == 0 ? INFINITY : object->collisionDate(ray);
}

Color Scene::color (const Ray &ray, const int remainingDepth) const
{
    if (remainingDepth == 0) {
        return m_backgroundColor;
    }

    Object *object = m_accelerationStructure->getObjectIntersecting(ray);
    if (object == 0) {
        return m_backgroundColor;
    }

    const Object::Collision collision = object->collision(ray);

    const Vect intersection = ray.pos() + collision.date*ray.dir();

    Color finalColor;

    for (const Light *light : lights()) {
        Vect toLight = light->pos() - intersection;
        toLight.normalize();

        double dotProduct = collision.normal * toLight;

        if (dotProduct >= 0) {
            Ray nextRay (intersection, toLight);
            nextRay.moveByEpsilon();

            if (collisionDate(nextRay) >= Vect::dist(intersection, light->pos())) {
                Color color (dotProduct * collision.material.color().red(),
                             dotProduct * collision.material.color().green(),
                             dotProduct * collision.material.color().blue());
                color *= light->intensity();

                finalColor += color;
            }
        }
    }

    // Reflection
    if (collision.material.reflectionCoef() != 0) {
        const Vect n = collision.normal;
        Vect nextDir = ray.dir() - 2 * (ray.dir() * n) * n;

        Ray nextRay (intersection, nextDir);
        nextRay.moveByEpsilon();

        Color nextColor = color(nextRay, remainingDepth-1);
        nextColor *= collision.material.reflectionCoef();

        finalColor += nextColor;
    }

    // Refraction
    if (collision.material.refractionCoef() != 0) {
        Vect n = collision.normal;

        // Snell's law
        double n1 = 1;
        double n2 = collision.material.refractiveIndex();

        double cosTheta1 = ray.dir() * n;

        if (cosTheta1 < 0) {
            cosTheta1 = -cosTheta1;
        }
        else {
            swap(n1, n2);
            n *= -1;
        }

        const double r = n1 / n2;
        const double k = 1 - r*r * (1 - cosTheta1*cosTheta1);

        if (k >= 0) { // No refraction otherwise
            Vect nextDir = r * ray.dir() + (r * cosTheta1 - sqrt(k)) * n;
            nextDir.normalize();

            Ray nextRay (intersection, nextDir);
            nextRay.moveByEpsilon();

            Color nextColor = color(nextRay, remainingDepth-1);
            nextColor *= collision.material.refractionCoef();

            finalColor += nextColor;
        }
    }

    return finalColor;
}
