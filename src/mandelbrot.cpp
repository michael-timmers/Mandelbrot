// #include <unordered_map>
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
    double tempX, xSquared = 0, ySquared = 0, w = 0;  // tricky variables
    double mag = 0;
    int n = 0, period = 0;
    double history[SEARCH_LIMIT];

    for (; n < limit; n++) {
        // z=z^2+c
        tempX = (xSquared - ySquared) + c_x;
        z_y = w - mag + c_y;  // 2*x*y+c
        z_x = tempX;

        xSquared = z_x * z_x;
        ySquared = z_y * z_y;
        w = (z_x + z_y) * (z_x + z_y);

        mag = xSquared + ySquared;
        if (mag >= 4)
            break;

        period = n + 1 - std::distance(history, std::find(history, history + n, mag));
        if (period > 0) {
            // std::cout << "found" << std::endl;
            return SDL_MapRGBA(renderer::canvas->format, 0, 0, 1023 / (period + 3), 255);
        }
        history[n] = mag;
    }

    // past the search limit
    return SDL_MapRGBA(renderer::canvas->format, 255, 255, 255 - 255 * n / limit, 255);
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