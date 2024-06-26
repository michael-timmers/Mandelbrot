#include <algorithm>

#include "headers.hpp"
#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot()
    : scale((double)3 / winWidth),  // scale*winWidth = 4
      lowerXBound(-2),
      lowerYBound(-1.5),
      panDistance(winWidth / 4) {
}

int Mandelbrot::hyperbolicColour(int dilation, int shift, int x) {
    return dilation / (x + shift);
}

Uint32 Mandelbrot::mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    return r << 24 | g << 16 | b << 8 | a;
}

Uint32 Mandelbrot::fn(double c_x, double c_y, int limit) {
    double z_x = 0, z_y = 0, xSquared = 0, ySquared = 0,
           z_x2, z_y2, xSquared2, ySquared2,
           w = 0, mag = 0, distance = 0;
    int n = 0;

    for (; n < limit && mag < 4; n++) {
        z_x2 = z_x;
        z_y2 = z_y;
        xSquared2 = xSquared;
        ySquared2 = ySquared;

        // z=z^2+c
        z_x = (xSquared - ySquared) + c_x;
        z_y = w - mag + c_y;  // 2*x*y+c

        xSquared = z_x * z_x;
        ySquared = z_y * z_y;
        w = (z_x + z_y) * (z_x + z_y);

        mag = xSquared + ySquared;
        distance += mag - (z_x + z_x) * z_x2 + xSquared2 - (z_y + z_y) * z_y2 + ySquared2;  // (x2-x1)^2+(y2-y1)^2
        // distance += mag;
    }

    // past range
    if (mag >= 4)
        return mapRGBA(255, 255, hyperbolicColour(1023, 3, n), 255);

    // still inside range
    return mapRGBA(0, 0, 255 - hyperbolicColour(16384, 63, distance), 255);
}

// from bound 1 to bound 2
double mapValue(double val, double lower1, double upper1, double lower2, double upper2) {
    double diff1 = upper1 - lower1, diff2 = upper2 - lower2;
    double originDistance1 = 0 - lower1, originDistance2 = 0 - lower2;
    return (val + originDistance1) / diff1 * diff2 - originDistance2;
}

void Mandelbrot::zoomIn(int x, int y) {
    double scaledX = mapValue(x, 0, winWidth, lowerXBound, lowerXBound + scale * winWidth);
    double scaledY = mapValue(y, 0, winHeight, lowerYBound, lowerYBound + scale * winHeight);

    double newScale = scale * (double)3 / 4;
    lowerXBound = scaledX - newScale * x;
    lowerYBound = scaledY - newScale * y;

    scale = newScale;

    // std::cout << "zooming into " << scaledX << "," << scaledY << " or: " << x << ", " << y << "\n";
    // std::cout << "bounds:" << lowerXBound << "," << lowerYBound << "\n";
}

void Mandelbrot::zoomOut(int x, int y) {
    double newScale = scale * (double)4 / 3;
    double scaledX = mapValue(x, 0, winWidth, lowerXBound, lowerXBound + scale * winWidth);
    double scaledY = mapValue(y, 0, winHeight, lowerYBound, lowerYBound + scale * winHeight);
    lowerXBound = scaledX - newScale * x;
    lowerYBound = scaledY - newScale * y;

    scale = newScale;

    // std::cout << "zooming into " << scaledX << "," << scaledY << " or: " << x << ", " << y << "\n";
    // std::cout << "bounds:" << lowerXBound << "," << lowerYBound << "\n";
}

void Mandelbrot::panLeft() {
    lowerXBound += scale * panDistance;
}

void Mandelbrot::panRight() {
    lowerXBound -= scale * panDistance;
}

void Mandelbrot::panUp() {
    lowerYBound -= scale * panDistance;
}

void Mandelbrot::panDown() {
    lowerYBound += scale * panDistance;
}

void Mandelbrot::reset() {
    lowerXBound = -2;
    lowerYBound = -1.5;
    scale = (double)3 / winWidth;
}
