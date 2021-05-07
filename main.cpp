#include <QApplication>
#include <QMainWindow>
#include <QImage>
#include <QLabel>

#include <iostream>
#include <iomanip>

#include "renderer/Stats.hpp"
#include "image_utility.hpp"

// (1) Update to change the scene
#include "scenes/waves.hpp"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);

#if 1
    renderWaves();
#else
    Stats::init();

    // (2) Update to change the scene
    Image *image = generateImageTeapot();

    Stats::endTimer();
    Stats::print(std::cout);

    showImage(*image);
#endif

    return app.exec();
}
