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

// Spheres
#if 0
    m_scene->addObject(new Sphere (m_scene, Vect(0, 0, 0), 1, Material(Color(255, 0, 0))));
    m_scene->addObject(new Sphere (m_scene, Vect(-3, -2, 0), 1, Material(Color(0, 255, 0)))); // Left
    m_scene->addObject(new Sphere (m_scene, Vect(-3, 2, 0), 1, Material(Color(0, 0, 255)))); // Right

    m_scene->addLight(new Light(Vect(3, 2, 2)));

    m_scene->camera()->setPos( Vect (10, 0, 0) );
    m_scene->camera()->setDir( Vect (-3, 0, 0) );
#endif

// Teapot
#if 0
    load("../teapot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (12, 12, 7.4) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );
#endif

// Torus knot
#if 1
    load("../knot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (14, 14, 6.8) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );
#endif

    // Create UI
    QImage image = QImage (m_scene->camera()->width(), m_scene->camera()->height(), QImage::Format_RGB32);

    m_scene->camera()->color(0, m_scene->camera()->height()/2);

    for (int x=0; x<m_scene->camera()->width(); x++) {
        for (int y=0; y<m_scene->camera()->height(); y++) {
            image.setPixel(x, m_scene->camera()->height()-y-1, m_scene->camera()->color(x, y).hex());
        }
    }

    // Disable resizing
    setFixedSize(m_scene->camera()->width(), m_scene->camera()->height());

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(image));
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
}

void MainWindow::load (QString filename)
{
    Group *group = new Group (m_scene);
    Material material (Color(255, 0, 0));

    fstream file (filename.toStdString().c_str(), fstream::in);

    vector<Vect> vertice;

    string line;
    while (getline(file, line)) {
        stringstream stream;
        stream << line;

        if (line[0] == 'v' && line[1] == ' ') {
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
    }

    m_scene->addObject(group);
}
