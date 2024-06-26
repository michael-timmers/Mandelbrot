#pragma once

#include "headers.hpp"

class Mandelbrot {
   public:
    double scale;
    double lowerXBound;
    double lowerYBound;
    double panDistance;

    Mandelbrot();

    // returns the colour for specified point
    Uint32 fn(double c_x, double c_y, int n);

    void zoomIn(int x, int y);
    void zoomOut(int x, int y);

    void panLeft();
    void panRight();
    void panUp();
    void panDown();
    void reset();

   private:
    int hyperbolicColour(int dilation, int shift, int x);
    Uint32 mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};