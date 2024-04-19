#pragma once
#include <memory>

#include "mandelbrot.hpp"
#include "renderer.hpp"

class AppManager {
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Mandelbrot> mandelbrot;

   public:
    AppManager();

    // a console output
    void intro();

    // initialises all SDL and TTF variables
    int init();

    void run(bool runProfiling = false, int numLoops = 5);

    void saveAsPng();

    // destroys all variables from SDL
    void quit();

    ~AppManager();
};