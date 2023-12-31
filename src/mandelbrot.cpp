#include <complex>
#include <memory>

#include "headers.hpp"
#include "mandelbrot.hpp"
#include "element.hpp"

namespace mandelbrot {

double scale = (double)4 / 800;
double xOffset = 0;
double yOffset = 0;

std::unique_ptr<Element> fn(std::complex<double> c, int n) {
    Element elem;

    // check if out of bounds
    // check if already has stable period
    // check if less than the current search limit
    while (elem.mag < 2 && elem.period == 0 && elem.n <= n) {
        elem.step(c);
    }

    // create a pointer
    return std::make_unique<Element>(elem);
}

void zoomIn(int x, int y) {
    scale *= (double)3 / 4;
    xOffset += xOffset - x;
    yOffset += y - yOffset;
}

void zoomOut(int x, int y) {
    mandelbrot::scale /= (double)3 / 4;
    mandelbrot::xOffset = mandelbrot::scale * (winWidth - x) / 2;
    mandelbrot::yOffset = mandelbrot::scale * (winHeight - y) / 2;
}

}  // namespace mandelbrot