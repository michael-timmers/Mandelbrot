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
    renderer::present();

    // event handler loops until input is given, then things are updated..
    while (eventHandler::handleInput()) {
        renderer::clear();

        timer::start();
        renderer::drawPoint(0, 0);
        timer::stop();

        renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        std::cout << "render time:" << timer::result() / 1000 << "micro seconds"
                  << "\n";

        renderer::present();

        SDL_Delay(10);
    }
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils