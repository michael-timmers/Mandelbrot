#include "headers.hpp"
#include "mandelbrot.hpp"

namespace eventHandler {

// SDL variable
SDL_Event event;

bool handleInput() {
    while (true) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            mandelbrot::zoomIn(x, winHeight - y);  // since 0, 0 is top left
                            return true;
                        case SDL_BUTTON_RIGHT:
                            SDL_GetMouseState(&x, &y);
                            mandelbrot::zoomOut(x, winHeight - y);
                            return true;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(10);
    }
}

}  // namespace eventHandler