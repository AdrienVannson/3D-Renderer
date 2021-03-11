#include "waves.hpp"
#include "image_utility.hpp"
#include "renderer/Scene.hpp"
#include "renderer/objects/Triangle.hpp"
#include "renderer/acceleration-structures/Octree.hpp"

#include <iostream>
#include <array>

using namespace std;

// Maillage du sol
const int N = 40;
array<array<double,N>,N> h;
array<array<double,N>,N> h2; // h2 = dh/dt

const double C = 0.3; // Pour la relation de dispersion

double t = 0;

void nextFrameWaves(const double delta_t)
{
    t += delta_t;

    array<array<double,N>,N> prevH = h;

    // Update h
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == 10 && j >= 5 && j <= 35) {
                h[i][j] = 0.05 * sin(2*M_PI*t);
            }
            else {
                h[i][j] += delta_t * h2[i][j];
            }
        }
    }

    // Update h2
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == 0 || i == N-1) {
                h2[i][j] = 0;
            }
            else if (j == 0) {
                // Dérivées secondes
                const double d2_x = (prevH[i-1][j] + prevH[i+1][j] - 2*prevH[i][j]) * (N-1) * (N-1);
                const double d2_y = (prevH[i][j+1] - prevH[i][j]) * (N-1) * (N-1);

                h2[i][j] += delta_t * C*C * (d2_x + d2_y);
            }
            else if (j == N-1) {
                // Dérivées secondes
                const double d2_x = (prevH[i-1][j] + prevH[i+1][j] - 2*prevH[i][j]) * (N-1) * (N-1);
                const double d2_y = (prevH[i][j-1] - prevH[i][j]) * (N-1) * (N-1);

                h2[i][j] += delta_t * C*C * (d2_x + d2_y);
            }
            else {
                // Dérivées secondes
                const double d2_x = (prevH[i-1][j] + prevH[i+1][j] - 2*prevH[i][j]) * (N-1) * (N-1);
                const double d2_y = (prevH[i][j-1] + prevH[i][j+1] - 2*prevH[i][j]) * (N-1) * (N-1);

                h2[i][j] += delta_t * C*C * (d2_x + d2_y);
            }
        }
    }
}

Image* generateImage()
{
    Scene *scene = new Scene;
    scene->initRender();
    scene->setBackgroundColor(Color(50, 50, 50));
    scene->setAccelerationStructure(new Octree);

    scene->addLight(new Light(Vect(-2, -4, 10), 1));

#if 0
    scene->camera()->setWidth(1920);
    scene->camera()->setHeight(1080);
#endif

    scene->camera()->setPos(Vect(0.5, -2.7, 1));
    scene->camera()->setDir(1.5 * Vect(0, 3, -1));

    for (int i=0; i<N-1; i++) {
        for (int j=0; j<N-1; j++) {
            const double x = i / (N - 1.);
            const double y = j / (N - 1.);
            const double d = 1. / (N - 1.);

            Triangle *t = new Triangle(
                Vect(x, y, h[i][j]),
                Vect(x+d, y, h[i+1][j]),
                Vect(x, y+d, h[i][j+1]),
                Material(Color(0, 0, 180))
            );

            scene->addObject(t);
        }
    }

    return scene->camera()->image();
}

void renderWaves()
{
    // Simulation
    const int fps = 60;
    const int duration = 12; // in seconds

    // Avancer de 3 secondes
    /*for (int i=0; i<3*100*fps; i++) {
        nextFrameWaves(1. / (100 * fps));
    }*/

    for (int i=0; i<duration*fps; i++) {
        const int process = 1; // Update to render different parts of the animation
        const int processCount = 1;

        if (i >= fps*duration*process/processCount && i < fps*duration*(process+1)/processCount) {
            Image *image = generateImage();

            std::string filename = std::to_string(i);
            filename = "output" + std::to_string(process) + "/"
                     + std::string(4 - filename.length(), '0') + filename + ".png";

            saveImage(*image, filename);
            delete image;
        }

        for (int i=0; i<100; i++) {
            nextFrameWaves(1. / (100 * fps));
        }
    }

    exit(0);

    // To create a video:
    // ffmpeg -framerate 60 -i %04d.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
}
