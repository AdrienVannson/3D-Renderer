#include "Mainwindow.hpp"

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

#define SCENE 8

#if SCENE == 1 // Spheres
    load(":/resources/floor.obj", {
             Material(Color(100, 100, 100)),
             Material(Color(50, 50, 50))
    });

    m_scene->addObject(new Sphere (m_scene, Vect(-1, 0, 1), 1, Material(Color(255, 0, 0))));
    m_scene->addObject(new Sphere (m_scene, Vect(-1, -2.1, 1), 1, Material(Color(0, 255, 0)))); // Left
    m_scene->addObject(new Sphere (m_scene, Vect(-1, 2.1, 1), 1, Material(Color(0, 0, 255), 0.6))); // Right

    m_scene->addLight(new Light(Vect(3, 2, 2)));

    m_scene->camera()->setPos( Vect (10, 0, 1) );
    m_scene->camera()->setDir( Vect (-3, 0, 0) );

#elif SCENE == 2 // Teapot
    load(":/resources/teapot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (12, 12, 7.4) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );

#elif SCENE == 3 // Monkey (with mirrors)
    load(":/resources/monkey.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    // Add mirror 1
    Vect a1 (20, -2, 0);
    Vect b1 (-10, -2, -10);
    Vect c1 (-10, -2, 10);
    m_scene->addObject(new Triangle (m_scene, a1, b1, c1, Material(Color(0, 0, 0), 1)));

    // Add mirror 2
    Vect a2 (-2, 20, 0);
    Vect b2 (-2, -10, -10);
    Vect c2 (-2, -10, 10);
    m_scene->addObject(new Triangle (m_scene, a2, b2, c2, Material(Color(0, 0, 0), 1)));

    m_scene->camera()->setPos( Vect (12, 12, 6.8) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );

#elif SCENE == 4 // Torus knot
    load(":/resources/knot.obj");

    m_scene->addLight(new Light(Vect(3, 2, 4)));

    m_scene->camera()->setPos( Vect (14, 14, 6.8) );
    m_scene->camera()->setDir( Vect (-3, -3, -1.5) );

#elif SCENE == 5 // Profile picture
    load(":/resources/profile_picture.obj", {Material(Color(144, 214, 117)), Material(Color(255, 42, 24))});

    m_scene->setBackgroundColor(Color (39, 123, 255)); // Blue

    m_scene->addLight(new Light(Vect(5, -3, 6)));

    m_scene->camera()->setPos( Vect (7, -7, 1.75) );

    Vect dir = -m_scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;

    m_scene->camera()->setDir( dir );

    m_scene->camera()->setWidth(256);
    m_scene->camera()->setHeight(256);

#elif SCENE == 6 // Sphere (mirror effect)
    load(":/resources/checkerboard.obj", {
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0)),
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0)),
            Material(Color(255, 255, 255)),
            Material(Color(0, 0, 0))
    });

    m_scene->addObject(new Sphere(m_scene, Vect(8, 8, 4), 4, Material(Color(0, 0, 0), 1)));

    m_scene->addLight(new Light(5*Vect(8, 20, 12)));

    m_scene->camera()->setPos( 30*Vect(1, 1, 1) );

    Vect dir = -m_scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;

    m_scene->camera()->setDir( dir );

    m_scene->camera()->setWidth(1024);
    m_scene->camera()->setHeight(1024);
#elif SCENE == 7 // Multiple lights
    load(":/resources/floor.obj", {
             Material(Color(100, 100, 100)),
             Material(Color(50, 50, 50))
    });

    m_scene->addObject(new Sphere(m_scene, Vect(0, 0, 3), 2, Material(Color(255, 0, 0))));

    m_scene->addLight(new Light(Vect(0, 50, 150), 0.5));
    m_scene->addLight(new Light(Vect(0, -50, 150), 0.5));
    m_scene->camera()->setPos(Vect(30, 0, 6));

    Vect dir = -m_scene->camera()->pos();
    dir.normalize();
    dir *= 2.5;
    m_scene->camera()->setDir( dir );
#elif SCENE == 8 // Sphere with refraction
    m_scene->setBackgroundColor(Color(40, 120, 255));

    load(":/resources/floor.obj", {
             Material(Color(255, 0, 0)),
             Material(Color(0, 0, 255))
    });

    Material material (Color(50, 50, 50));
    material.setRefractionCoef(0.8);
    material.setRefractiveIndex(1.3);

    m_scene->addObject(new Sphere (m_scene, Vect(5, 0, 1), 1, material));

    m_scene->addLight(new Light(Vect(6, 2, 5)));

    m_scene->camera()->setPos( Vect (17, -0.5, 5) );
    m_scene->camera()->setDir( Vect (-3, 0.1, -1) );
#endif


    // Create UI
    QImage image = QImage (m_scene->camera()->width(), m_scene->camera()->height(), QImage::Format_RGB32);

    for (int x=0; x<m_scene->camera()->width(); x++) {
        for (int y=0; y<m_scene->camera()->height(); y++) {
            image.setPixel(x, m_scene->camera()->height()-y-1, m_scene->camera()->color(x, y, 10).hex());
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
