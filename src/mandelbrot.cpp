#include <algorithm>

#include "headers.hpp"
#include "mandelbrot.hpp"
#include "renderer.hpp"

namespace mandelbrot {

double scale = (double)4 / 800;
double lowerXBound = -2;
double lowerYBound = -2;

// colour lookup tables
// std::unordered_map<int, Uint8> escapeColours;
// std::unordered_map<int, Uint8> periodColours;

// initialise colour lookup tables
int init() {
    return 0;
}

Uint32 fn(double c_x, double c_y, int limit) {
    double z_x = 0, z_y = 0;
    double xSquared = 0, ySquared = 0, w = 0;  // tricky variables
    double tempX, tempY, tempXSq, tempYSq,
        mag = 0, distance = 0;
    int n = 0;

    for (; n < limit; n++) {
        tempX = z_x;
        tempY = z_y;

        // z=z^2+c
        z_x = (xSquared - ySquared) + c_x;
        z_y = w - mag + c_y;  // 2*x*y+c

        tempXSq = xSquared;
        tempYSq = ySquared;

        xSquared = z_x * z_x;
        ySquared = z_y * z_y;
        w = (z_x + z_y) * (z_x + z_y);

        mag = xSquared + ySquared;
        distance += xSquared + 2 * z_x * tempX + tempXSq + ySquared + 2 * z_y * tempY + tempYSq;
        // distance += mag;

        if (mag >= 4)
            return SDL_MapRGBA(renderer::canvas->format, 255, 255, 1023 / (n + 3), 255);
    }

    // past the search limit
    return SDL_MapRGBA(renderer::canvas->format, 0, 0, 32767 / (distance + 127), 255);
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