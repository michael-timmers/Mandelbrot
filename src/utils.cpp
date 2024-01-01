#include "headers.hpp"
#include "eventHandler.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

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
    //  int sumTime = 0, numLoops = 0;

    // initally render
    renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);
    renderer::present();

    // event handler loops until input is given, then things are updated..
    while (eventHandler::handleInput()) {
        renderer::clear();

        // auto start = std::chrono::high_resolution_clock::now();

        renderer::renderMandelbrot(mandelbrot::scale, mandelbrot::lowerXBound, mandelbrot::lowerYBound);

        // auto finish = std::chrono::high_resolution_clock::now();

        // sumTime += std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();

        // if(numLoops++%20 == 0){
        // std::cout << "graph render time:" << (sumTime/20) << "microseconds" << "\n";
        // sumTime = 0;
        // }

        renderer::present();

        SDL_Delay(10);
    }
}

void kill() {
    renderer::kill();

    SDL_Quit();
}
}  // namespace utils