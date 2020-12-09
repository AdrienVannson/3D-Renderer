#include "image_utility.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>

QImage convertToQImage (const Image &img)
{
    QImage qimage (img.width(), img.height(), QImage::Format_RGB32);
    for (int x=0; x<img.width(); x++) {
        for (int y=0; y<img.height(); y++) {
            qimage.setPixel(x, img.height()-y-1, img.color(x, y).hex());
        }
    }
    return qimage;
}

void saveImage (const Image &img, const std::string filename)
{
    convertToQImage(img).save(QString::fromStdString(filename));
}

void showImage (const Image &img)
{
    QMainWindow *window = new QMainWindow;
    window->setFixedSize(img.width(), img.height());

    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(convertToQImage(img)));
    window->setCentralWidget(label);

    window->show();
    qApp->processEvents();
}
