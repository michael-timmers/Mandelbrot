#pragma once
#include <complex>

#include "headers.hpp"
#include "element.hpp"

namespace mandelbrot {

extern int totalSearchSteps;

extern Element set[winWidth][winHeight];

extern double scale;
extern double xOffset;
extern double yOffset;

Element* fn(std::complex<double> c, int x, int y, int n);

void zoomIn(int x, int y);
void zoomOut(int x, int y);

}  // namespace mandelbrot