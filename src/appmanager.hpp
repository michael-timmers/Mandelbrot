#pragma once
#include <memory>

class AppManager;

#include "mandelbrot.hpp"
#include "renderer.hpp"
#include "eventHandler.hpp"

class AppManager {
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Mandelbrot> mandelbrot;
    std::unique_ptr<EventHandler> eventHandler;

   public:
    const int SEARCH_LIMIT;

    AppManager(const int _SEARCH_LIMIT);

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