#include "Mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create scene
    m_scene = new Scene ();
    m_scene->camera()->setWidth(1920);
    m_scene->camera()->setHeight(1080);

    m_scene->addObject(new Sphere (m_scene, Vect(0, 0, 0), 1, Material(Color(255, 0, 0))));
    m_scene->addObject(new Sphere (m_scene, Vect(-3, -2, 0), 1, Material(Color(0, 255, 0)))); // Left
    m_scene->addObject(new Sphere (m_scene, Vect(-3, 2, 0), 1, Material(Color(0, 0, 255)))); // Right

    m_scene->addLight(new Light(Vect(1, 1, 1)));

    m_scene->camera()->setPos( Vect (10, 0, 0) );
    m_scene->camera()->setDir( Vect (-3, 0, 0) );

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
