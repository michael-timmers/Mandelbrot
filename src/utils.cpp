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

    if (mandelbrot::init() == 1)
        return 1;

    return 0;  // success
}

void run(bool runProfiling) {
    // profiling variables:
    int timeSum = 0, numLoops = 0, mandelbrotTime, renderTime;

    // event handler loops until input is given, then things are updated..
    do {
        // renderer::clear();

        timer::start();
        // renderer::renderLegacyMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
        timer::stop();

        mandelbrotTime = timer::result().count() / 1000000;
        std::cout << "Mandelbrot time:" << mandelbrotTime << "milliseconds"
                  << "\n";

        timer::start();
        renderer::updateWindowSurfaceWithCanvas();
        // renderer::present();
        timer::stop();

        renderTime = timer::result().count() / 1000000;
        std::cout << "Update time:" << renderTime << "milliseconds"
                  << "\n";

        if (runProfiling) {
            numLoops++;
            timeSum += mandelbrotTime;
            timeSum += renderTime;
            if (numLoops == 5) {
                std::cout << "average time:" << timeSum / 5 << "\n";
                timeSum = 0;
                break;
            }
        }

        SDL_Delay(10);
    } while (runProfiling || eventHandler::handleInput());
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils