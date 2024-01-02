#pragma once
#include <memory>

#include "headers.hpp"
#include "element.hpp"

namespace mandelbrot {

extern double scale;
extern double lowerXBound;
extern double lowerYBound;

std::unique_ptr<Element> fn(double c_x, double c_y, int n);

void zoomIn(int x, int y);
void zoomOut(int x, int y);

}  // namespace mandelbrot