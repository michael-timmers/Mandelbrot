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
    // initally render
    renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
    // renderer::renderTest();

    renderer::updateWindowSurfaceWithCanvas();
    // renderer::present();

    // event handler loops until input is given, then things are updated..
    while (eventHandler::handleInput()) {
        // renderer::clear();

        timer::start();
        renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        timer::stop();

        std::cout << "Mandelbrot time:" << timer::result().count() / 1000000 << "milliseconds"
                  << "\n";

        timer::start();
        renderer::updateWindowSurfaceWithCanvas();
        // renderer::present();
        timer::stop();

        std::cout << "Update time:" << timer::result().count() / 1000000 << "milliseconds"
                  << "\n";

        SDL_Delay(10);
    }
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils