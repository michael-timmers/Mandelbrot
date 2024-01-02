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
    // profiling variables
    int sumTime = 0, numLoop = 0;

    // initally render
    renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
    renderer::present();

    // event handler loops until input is given, then things are updated..
    while (eventHandler::handleInput()) {
        renderer::clear();

        timer::start();
        renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        timer::finish();

        sumTime += timer::result();

        if (numLoops++ % 20 == 0) {
            std::cout << "render time:" << (sumTime / 20) << "nano seconds"
                      << "\n";
            sumTime = 0;
        }

        renderer::present();

        SDL_Delay(10);
    }
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils