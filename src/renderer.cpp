#include <memory>

#include "headers.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

Renderer::Renderer()
    : window(SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED)),
      window_surface(SDL_GetWindowSurface(window)),
      canvas(SDL_CreateRGBSurfaceWithFormat(
          0, winWidth, winHeight, 32, SDL_PIXELFORMAT_RGBA8888)),
      canvasBuffer(static_cast<Uint32 *>(canvas->pixels)) {
    std::cout << "renderer constructed" << std::endl;
}

void Renderer::renderMandelbrot(const std::unique_ptr<Mandelbrot> &mandelbrot) {
    Uint32 colour;

    double scaledX, scaledY = mandelbrot->lowerYBound;
    int linearPos = 0;

    SDL_LockSurface(this->canvas);
    for (int y = 0; y < winHeight; y++, scaledY += mandelbrot->scale) {
        scaledX = mandelbrot->lowerXBound;
        for (int x = 0; x < winWidth; x++, scaledX += mandelbrot->scale) {
            colour = mandelbrot->fn(scaledX, scaledY, SEARCH_LIMIT);

            this->canvasBuffer[linearPos++] = colour;
        }
    }
    SDL_UnlockSurface(this->canvas);
}

void Renderer::saveAsPng(const char *path) {
    IMG_SavePNG(this->window_surface, path);
}

void Renderer::updateWindowSurfaceWithCanvas() {
    SDL_BlitSurface(this->canvas, NULL, this->window_surface, NULL);
    SDL_UpdateWindowSurface(this->window);
}

Renderer::~Renderer() {
    // SDL_FreeSurface(this->canvas);
    // SDL_FreeSurface(this->window_surface);
    SDL_DestroyWindow(this->window);
    std::cout << "renderer destructed" << std::endl;
}
