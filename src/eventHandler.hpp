#pragma once

#include <memory>

#include "mandelbrot.hpp"

class EventHandler {
    // SDL variable
    SDL_Event event;

   public:
    bool handleInput(const std::unique_ptr<Mandelbrot>& mandelbrot);
};