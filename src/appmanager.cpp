#include <memory>

#include "headers.hpp"
#include "appmanager.hpp"
#include "eventHandler.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

void AppManager::intro() {
    std::cout << "mandelbrot Set\n";
}

int AppManager::init() {
    SDL_Init(SDL_INIT_VIDEO);

    renderer = std::make_unique<Renderer>();

    return 0;  // success
}

void AppManager::run(bool runProfiling, int numLoops) {
    int i = 0;

    // event handler loops until input is given, then things are updated..
    do {
        renderer->renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);

        renderer->updateWindowSurfaceWithCanvas();

        i++;

        SDL_Delay(10);
    } while ((runProfiling && i < numLoops) || (!runProfiling && eventHandler::handleInput()));
}

void AppManager::saveAsPng(double lowerXBound, double lowerYBound, double scale) {
    renderer->renderMandelbrot(scale, lowerXBound, lowerYBound);
    renderer->updateWindowSurfaceWithCanvas();

    renderer->saveAsPng(("../images/img" + std::to_string(SEARCH_LIMIT) + ".png").c_str());
}

void AppManager::kill() {
    renderer->~Renderer();

    SDL_Quit();
    std::cout << "qquit" << std::endl;
}