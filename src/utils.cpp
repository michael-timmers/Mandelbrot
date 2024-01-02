#include "headers.hpp"
#include "eventHandler.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"
#include "timer.hpp"

namespace utils {

void intro() {
    std::cout << "mandelbrot Set\n";
}

int init() {
    SDL_Init(SDL_INIT_VIDEO);

    if (renderer::init() == 1)
        return 1;  // window or renderer not created.

    return 0;  // success
}

void run() {
    // event handler loops until input is given, then things are updated..
    do {
        renderer::clear();

        timer::start();
        renderer::renderLegacyMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        timer::stop();

        std::cout << "Mandelbrot time:" << timer::result().count() / 1000000 << "milliseconds"
                  << "\n";

        timer::start();
        // renderer::updateWindowSurfaceWithCanvas();
        renderer::present();
        timer::stop();

        std::cout << "Update time:" << timer::result().count() / 1000000 << "milliseconds"
                  << "\n";

        SDL_Delay(10);
    } while (eventHandler::handleInput());
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils