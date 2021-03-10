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
    const clock_t startTime = clock();

    // (2) Update to change the scene
    Image *image = generateImageTeapot();

    const clock_t endTime = clock();

    // Show stats
    const int width1 = 40;
    const int width2 = 16;

    std::cout.imbue(std::locale("")); // Pretty print numbers
    std::cout << "##### Statistics\n";

    std::cout << std::left  << std::setw(width1) << "Total CPU time:"
              << std::right << std::setw(width2-2) << (double)(endTime-startTime) / CLOCKS_PER_SEC << " s\n";

    std::cout << std::left  << std::setw(width1) << "Ray-triangle tests count:"
              << std::right << std::setw(width2) << Stats::rayTriangleTestsCount() << "\n";
    std::cout << std::left  << std::setw(width1) << "Ray-triangle intersections count:"
              << std::right << std::setw(width2) << Stats::rayTriangleIntersectionsCount() << "\n";

    std::cout << std::left  << std::setw(width1) << "Ray-box tests count:"
              << std::right << std::setw(width2) << Stats::rayBoxTestsCount() << "\n";
    std::cout << std::left  << std::setw(width1) << "Ray-box intersections count:"
              << std::right << std::setw(width2) << Stats::rayBoxIntersectionsCount() << "\n";

    std::cout.flush();

    showImage(*image);
#endif

    return app.exec();
}
