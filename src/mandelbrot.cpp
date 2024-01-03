#include <unordered_map>

#include "headers.hpp"
#include "mandelbrot.hpp"
#include "element.hpp"
#include "renderer.hpp"

namespace mandelbrot {

double scale = (double)4 / 800;
double lowerXBound = -2;
double lowerYBound = -2;

// colour lookup tables
std::unordered_map<int, Uint8> escapeColours;
std::unordered_map<int, Uint8> periodColours;

// initialise colour lookup tables
int init() {
    for (int i = 0; i < SEARCH_LIMIT; i++) {
        escapeColours[i] = 255 - 255 * i / SEARCH_LIMIT;
        periodColours[i] = 1023 / (i + 3);
    }
    return 0;
}

Uint32 fn(double c_x, double c_y, int limit) {
    Element elem;

    // check if out of bounds
    // check if has stable period
    // check if less than the current search limit
    while (elem.n < limit) {
        elem.step(c_x, c_y);

        if (elem.mag >= 4) {
            break;
        } else if (elem.period > 0) {
            // std::cout << "found" << std::endl;
            return SDL_MapRGBA(renderer::canvas->format, 0, 0, 1023 / (elem.period + 3), 255);
        }
    }

    // past the search limit
    return SDL_MapRGBA(renderer::canvas->format, 255, 255, 255 - 255 * elem.n / limit, 255);
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