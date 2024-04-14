#include <memory>

#include "headers.hpp"
#include "eventHandler.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

namespace utils {

std::unique_ptr<Renderer> renderer;

void intro() {
    std::cout << "mandelbrot Set\n";
}

int init() {
    SDL_Init(SDL_INIT_VIDEO);

    renderer = std::make_unique<Renderer>();

    return 0;  // success
}

void run(bool runProfiling, int numLoops) {
    int i = 0;

    // event handler loops until input is given, then things are updated..
    do {
        renderer->renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);

        renderer->updateWindowSurfaceWithCanvas();

        i++;

        SDL_Delay(10);
    } while ((runProfiling && i < numLoops) || (!runProfiling && eventHandler::handleInput()));
}

void saveAsPng(double lowerXBound, double lowerYBound, double scale) {
    renderer->renderMandelbrot(scale, lowerXBound, lowerYBound);
    renderer->updateWindowSurfaceWithCanvas();

    renderer->saveAsPng(("../images/img" + std::to_string(SEARCH_LIMIT) + ".png").c_str());
}

void kill() {
    SDL_Quit();
}
}  // namespace utils