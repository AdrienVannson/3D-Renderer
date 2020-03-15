#include <sstream>

#include "Scene.hpp"
#include "objects/Triangle.hpp"

using namespace std;


Scene::Scene () :
    m_backgroundColor (Color(80, 80, 80))
{
    m_camera = new Camera (this);
}

Scene::~Scene ()
{
    delete m_camera;

    for (Object *object : m_objects) {
        delete object;
    }

    for (Light *light : m_lights) {
        delete light;
    }
}

double Scene::collisionDate (const Ray &ray) const
{
    double minCollisionDate = INFINITY;

    for (Object *object : m_objects) {
        minCollisionDate = min(object->collisionDate(ray), minCollisionDate);
    }

    return minCollisionDate;
}

Color Scene::color (const Ray &ray, const int remainingDepth) const
{
    if (remainingDepth == 0) {
        return m_backgroundColor;
    }

    Object *object = 0;
    double minCollisionDate = INFINITY;

    // Select nearest object
    for (Object *currentObject : m_objects) {
        const double collisionDate = currentObject->collisionDate(ray);

        if (collisionDate < minCollisionDate) {
            minCollisionDate = collisionDate;
            object = currentObject;
        }
    }

    if (isinf(minCollisionDate)) {
        return m_backgroundColor;
    }

    return object->color(ray, remainingDepth);
}

void Scene::load (QString filename, const std::vector<Material> &materials)
{
    Group *group = new Group (this);

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

                group->addObject(new Triangle(this,
                                              vertice[indexes[0]-1], vertice[indexes[1]-1], vertice[indexes[2]-1],
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
