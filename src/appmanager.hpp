#pragma once
#include <memory>

#include "mandelbrot.hpp"
#include "renderer.hpp"

class AppManager {
    std::unique_ptr<Renderer> renderer;

   public:
    // a console output
    void intro();

    // initialises all SDL and TTF variables
    int init();

    void run(bool runProfiling = false, int numLoops = 5);

    void saveAsPng(double lowerXBound = mandelbrot::lowerXBound, double lowerYBound = mandelbrot::lowerYBound, double scale = mandelbrot::scale);

    // destroys all variables from SDL and TTF
    void kill();
};