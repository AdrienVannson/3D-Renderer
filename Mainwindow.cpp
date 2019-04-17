#include "Mainwindow.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create scene
    m_scene = new Scene ();
#if 0
    m_scene->camera()->setWidth(1280);
    m_scene->camera()->setHeight(720);
#endif

#define SCENE 4

// Spheres
#if SCENE == 1
    m_scene->addObject(new Sphere (m_scene, Vect(0, 0, 0), 1, Material(Color(255, 0, 0))));
    m_scene->addObject(new Sphere (m_scene, Vect(-3, -2, 0), 1, Material(Color(0, 255, 0)))); // Left
    m_scene->addObject(new Sphere (m_scene, Vect(-3, 2, 0), 1, Material(Color(0, 0, 255)))); // Right

    m_scene->addLight(new Light(Vect(3, 2, 2)));

    m_scene->camera()->setPos( Vect (10, 0, 0) );
    m_scene->camera()->setDir( Vect (-3, 0, 0) );

// Teapot
#elif SCENE == 2
    load("../teapot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (12, 12, 7.4) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );

// Torus knot
#elif SCENE == 3
    load("../knot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (14, 14, 6.8) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );

// Profile picture
#elif SCENE == 4
    load("../profile_picture.obj", {Material(Color(144, 214, 117)), Material(Color(255, 42, 24))});

    m_scene->setBackgroundColor(Color (39, 123, 255)); // Blue

    m_scene->addLight(new Light(Vect(5, -3, 6)));

    m_scene->camera()->setPos( Vect (7, -7, 1.75) );

    Vect dir = -m_scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;

    m_scene->camera()->setDir( dir );

    m_scene->camera()->setWidth(256);
    m_scene->camera()->setHeight(256);
#endif

    // Create UI
    QImage image = QImage (m_scene->camera()->width(), m_scene->camera()->height(), QImage::Format_RGB32);

    for (int x=0; x<m_scene->camera()->width(); x++) {
        for (int y=0; y<m_scene->camera()->height(); y++) {
            image.setPixel(x, m_scene->camera()->height()-y-1, m_scene->camera()->color(x, y).hex());
        }
    }

    image.save("output.png", Q_NULLPTR, 100);

    // Disable resizing
    setFixedSize(m_scene->camera()->width(), m_scene->camera()->height());

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(image));
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
}

void MainWindow::load (QString filename, const std::vector<Material> &materials)
{
    Group *group = new Group (m_scene);

    int iObject = -1;
    vector<Vect> vertice;
    Material material;

    fstream file (filename.toStdString().c_str(), fstream::in);
    string line;

    while (getline(file, line)) {
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

                group->addObject(new Triangle(m_scene,
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

    m_scene->addObject(group);
}
