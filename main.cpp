#include <QApplication>

#include "Mainwindow.hpp"

// (1) Update to change the scene
#include "scenes/teapot.hpp"


int main (int argc, char *argv[])
{
    // (2) Update to change the scene
    Image *image = generateImageTeapot();

    QApplication a(argc, argv);

    // Convert to QImage
    QImage qimage (image->width(), image->height(), QImage::Format_RGB32);
    for (int x=0; x<image->width(); x++) {
        for (int y=0; y<image->height(); y++) {
            qimage.setPixel(x, image->height()-y-1, image->color(x, y).hex());
        }
    }

    // Display the image
    QMainWindow window;
    window.setFixedSize(image->width(), image->height());

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(qimage));
    window.setCentralWidget(label);

    window.show();

    return a.exec();
}
