#pragma once

#include <memory>

#include "headers.hpp"
#include "mandelbrot.hpp"

class Renderer {
    // SDL variables
    SDL_Window* window;

    // for fast access to pixels of window
    SDL_Surface* window_surface;
    SDL_Surface* canvas;
    Uint32* canvasBuffer;

    // changable.
    SDL_Color backgroundColour = {255, 255, 255};

   public:
    // set up renderer and window
    Renderer();

    void renderMandelbrot(const std::unique_ptr<Mandelbrot>& mandelbrot);

    void saveAsPng(const char* path);

    void updateWindowSurfaceWithCanvas();

    ~Renderer();
};