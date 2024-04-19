#include "headers.hpp"
#include "eventHandler.hpp"
#include "mandelbrot.hpp"

bool EventHandler::handleInput(const std::unique_ptr<Mandelbrot>& mandelbrot) {
    SDL_WaitEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            return false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mandelbrot->zoomIn(x, y);  // since 0, 0 is top left
                    return true;

                default:
                    break;
            }
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mandelbrot->zoomOut(x, y);
                    return true;
                case SDLK_r:
                    mandelbrot->reset();
                    return true;
                case SDLK_LEFT:
                    mandelbrot->panLeft();
                    return true;
                case SDLK_RIGHT:
                    mandelbrot->panRight();
                    return true;
                case SDLK_UP:
                    mandelbrot->panUp();
                    return true;
                case SDLK_DOWN:
                    mandelbrot->panDown();
                    return true;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return true;
}
