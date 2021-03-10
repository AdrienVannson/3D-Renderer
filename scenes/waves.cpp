#include "waves.hpp"
#include "image_utility.hpp"
#include "renderer/Scene.hpp"
#include "renderer/objects/Triangle.hpp"

#include <iostream>
#include <array>

using namespace std;

// Maillage du sol
const double COEF_VITESSE = 1;

const int N = 20;
array<array<double,N>,N> hauteurs;

void nextFrame()
{
    array<array<double,N>,N> ancien = hauteurs;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == 0 || i == N-1 || j == 0 || j == N-1) {
                hauteurs[i][j] = 0;
            }
            else if (i == 10 && j == 10) {
                hauteurs[i][j] = min(hauteurs[i][j] + 0.05, 0.2);
            }
            else {
                const double somme = hauteurs[i][j+1] + hauteurs[i][j-1]
                                   + hauteurs[i+1][j] + hauteurs[i-1][j];
                hauteurs[i][j] = COEF_VITESSE*somme/4 + (1-COEF_VITESSE)*ancien[i][j];
            }
        }
    }
}

Image* generateImage()
{
    Scene *scene = new Scene;
    scene->initRender();
    scene->setBackgroundColor(Color(50, 50, 50));

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
                Vect(x, y, hauteurs[i][j]),
                Vect(x+d, y, hauteurs[i+1][j]),
                Vect(x, y+d, hauteurs[i][j+1]),
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
    for (int i=0; i<60*60; i++) { // 60s, 60fps
        const int process = 0; // Update to render different parts of the animation

        if ( (process == 0 && i < 15*60)
          || (process == 1 && i >= 15*60 && i < 30*60)
          || (process == 2 && i >= 30*60 && i < 45*60)
          || (process == 3 && i >= 45*60) ) {
            Image *image = generateImage();

            std::string filename = std::to_string(i);
            filename = "output" + std::to_string(process) + "/"
                     + std::string(4 - filename.length(), '0') + filename + ".png";

            saveImage(*image, filename);
            //showImage(*image);

            delete image;
        }

        nextFrame(); // 60 fps
    }

    exit(0);

    // To create a video:
    // ffmpeg -framerate 60 -i %04d.png -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output.mp4
}
