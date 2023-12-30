#include <memory>

#include "headers.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"
#include "element.hpp"

namespace renderer {

// SDL variables
SDL_Renderer *renderer;
SDL_Window *window;

// changable.
SDL_Color backgroundColour = {255, 255, 255};
int lineThickness = 6;

int init() {
    window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);  // allows for rendering on textures.

    clear();
    return 0;  // success.
}

void clear() {
    SDL_SetRenderDrawColor(renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, 255);
    SDL_RenderClear(renderer);
}

void renderCopy(SDL_Texture *tex, const SDL_Rect *src, const SDL_Rect *dst) {
    SDL_RenderCopy(renderer, tex, src, dst);
}

SDL_Texture *createTexture(Uint32 format, int access, int w, int h) {
    return SDL_CreateTexture(renderer, format, access, w, h);
}

// returns a texture that was made from a surface
SDL_Texture *CreateTextureFromSurface(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

// null means taht the target will be reset
void changeRendrTarget(SDL_Texture *targetTex) {
    SDL_SetRenderTarget(renderer, targetTex);
}

// draws a line with the global variable 'lineThickness' as the thickness.
void drawThickLine(int x1, int y1, int x2, int y2, int thickness = lineThickness) {
    for (int j = -thickness / 2; j < thickness / 2; j++)
        SDL_RenderDrawLine(renderer, x1 + j, y1, x2 + j, y2);
}

void renderMandelbrot(double scale, double xOffset, double yOffset) {
    for (int x = 0; x < winWidth; x++) {
        for (int y = 0; y < winHeight; y++) {
            std::complex<double> c(x * scale - xOffset, y * scale - yOffset);
            Element *e = mandelbrot::fn(c, x, y, mandelbrot::totalSearchSteps);

            if (e->mag < 2 && e->period > 0)
                SDL_SetRenderDrawColor(renderer, 0, 0, 1023 / (e->period + 3), 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255 - 255 * e->n / mandelbrot::totalSearchSteps, 255);

            SDL_RenderDrawPoint(renderer, x, y);
        }
        // std::cout << x << "\n";
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void present() {
    SDL_RenderPresent(renderer);
}

void kill() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

}  // namespace renderer