#include <memory>

#include "headers.hpp"
#include "appmanager.hpp"
#include "eventHandler.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

AppManager::AppManager(const int _SEARCH_LIMIT)
    : renderer(std::make_unique<Renderer>(this)),
      mandelbrot(std::make_unique<Mandelbrot>()),
      eventHandler(std::make_unique<EventHandler>()),
      SEARCH_LIMIT(_SEARCH_LIMIT) {
    SDL_Init(SDL_INIT_VIDEO);
    std::cout << "mandelbrot Set\n";
}

void AppManager::run(bool runProfiling, int numLoops) {
    int i = 0;

    // event handler loops until input is given, then things are updated..
    do {
        renderer->renderMandelbrot(mandelbrot);

        renderer->updateWindowSurfaceWithCanvas();

        SDL_Delay(10);
    } while ((runProfiling && i++ < numLoops) || (!runProfiling && eventHandler->handleInput(mandelbrot)));
}

void AppManager::saveAsPng() {
    renderer->renderMandelbrot(mandelbrot);
    renderer->updateWindowSurfaceWithCanvas();

    renderer->saveAsPng(("../images/img" + std::to_string(SEARCH_LIMIT) + ".png").c_str());
}

AppManager::~AppManager() {
    SDL_Quit();
    std::cout << "qquit" << std::endl;
}