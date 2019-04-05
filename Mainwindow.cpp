#include "Mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create scene
    m_scene = new Scene ();

    m_scene->addObject(new Sphere (Vect(0, 0, 0), 1));

    m_scene->camera()->pos() = Vect (3, 0, 0);
    m_scene->camera()->dir() = Vect (-1, 0, 0);

    // Create UI
    QImage image = QImage (m_scene->camera()->width(), m_scene->camera()->height(), QImage::Format_RGB32);

    for (int x=0; x<m_scene->camera()->width(); x++) {
        for (int y=0; y<m_scene->camera()->height(); y++) {
            image.setPixel(x, y, m_scene->camera()->color(x, y).hex());
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
