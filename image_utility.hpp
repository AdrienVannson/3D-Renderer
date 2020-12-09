#ifndef IMAGEUTILITY_HPP
#define IMAGEUTILITY_HPP

#include "renderer/Image.hpp"

#include <string>
#include <QImage>

QImage convertToQImage (const Image &img);

void saveImage (const Image &img, const std::string filename);
void showImage (const Image &img);

#endif // IMAGEUTILITY_HPP
