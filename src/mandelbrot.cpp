#include <complex>

#include "headers.hpp"
#include "mandelbrot.hpp"
#include "element.hpp"

namespace mandelbrot {

int totalSearchSteps = SEARCH_INIT;

Element set[winWidth][winHeight];

double scale = (double)4 / 800;
double xOffset = 2;
double yOffset = 2;

Element* fn(std::complex<double> c, int x, int y, int n) {
    Element* elem = &set[x][y];

    // check if out of bounds
    // check if already has stable period
    // check if less than the current search limit
    while (elem->mag < 2 && elem->period == 0 && elem->n <= n) {
        elem->step(c);
    }
    return elem;
}

void zoomIn(int x, int y) {
    scale *= (double)3 / 4;
    xOffset = scale * (winWidth - x) / 2;
    yOffset = scale * (winHeight - y) / 2;

    // reset number of searches
    totalSearchSteps = SEARCH_INIT;
}

void zoomOut(int x, int y) {
    mandelbrot::scale /= (double)3 / 4;
    mandelbrot::xOffset = mandelbrot::scale * (winWidth - x) / 2;
    mandelbrot::yOffset = mandelbrot::scale * (winHeight - y) / 2;

    totalSearchSteps = SEARCH_INIT;
}

}  // namespace mandelbrot