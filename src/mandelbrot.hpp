#pragma once
#include <complex>

#include "headers.hpp"
#include "element.hpp"

namespace mandelbrot {

extern double scale;
extern double xOffset;
extern double yOffset;

Element fn(std::complex<double> c, int n);

void zoomIn(int x, int y);
void zoomOut(int x, int y);

}  // namespace mandelbrot