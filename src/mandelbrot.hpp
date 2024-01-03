#pragma once

#include "headers.hpp"
#include "element.hpp"

namespace mandelbrot {

extern double scale;
extern double lowerXBound;
extern double lowerYBound;

// returns the colour for specified point
Uint32 fn(double c_x, double c_y, int n);

void zoomIn(int x, int y);
void zoomOut(int x, int y);

}  // namespace mandelbrot