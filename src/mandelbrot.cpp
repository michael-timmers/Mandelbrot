#include <memory>

#include "headers.hpp"
#include "mandelbrot.hpp"
#include "element.hpp"

namespace mandelbrot {

double scale = (double)4 / 800;
double lowerXBound = -2;
double lowerYBound = -2;

std::unique_ptr<Element> fn(double c_x, double c_y, int n) {
    Element elem;

    // check if out of bounds
    // check if has stable period
    // check if less than the current search limit
    while (elem.mag < 2 && elem.period == 0 && elem.n <= n) {
        elem.step(c_x, c_y);
    }

    // create a pointer
    return std::make_unique<Element>(elem);
}

// from bound 1 to bound 2
double mapValue(double val, double lower1, double upper1, double lower2, double upper2) {
    double diff1 = upper1 - lower1, diff2 = upper2 - lower2;
    double originDistance1 = 0 - lower1, originDistance2 = 0 - lower2;
    return (val + originDistance1) / diff1 * diff2 - originDistance2;
}

void zoomIn(int x, int y) {
    double newScale = scale * (double)3 / 4;
    double scaledX = mapValue(x, 0, winWidth, lowerXBound, lowerXBound + scale * winWidth);
    double scaledY = mapValue(y, 0, winHeight, lowerYBound, lowerYBound + scale * winHeight);
    lowerXBound = scaledX - newScale * x;
    lowerYBound = scaledY - newScale * y;

    scale = newScale;

    // std::cout << "zooming into " << scaledX << "," << scaledY << " or: " << x << ", " << y << "\n";
    // std::cout << "bounds:" << lowerXBound << "," << lowerYBound << "\n";
}

void zoomOut(int x, int y) {
    double newScale = scale * (double)4 / 3;
    double scaledX = mapValue(x, 0, winWidth, lowerXBound, lowerXBound + scale * winWidth);
    double scaledY = mapValue(y, 0, winHeight, lowerYBound, lowerYBound + scale * winHeight);
    lowerXBound = scaledX - newScale * x;
    lowerYBound = scaledY - newScale * y;

    scale = newScale;

    // std::cout << "zooming into " << scaledX << "," << scaledY << " or: " << x << ", " << y << "\n";
    // std::cout << "bounds:" << lowerXBound << "," << lowerYBound << "\n";
}

}  // namespace mandelbrot