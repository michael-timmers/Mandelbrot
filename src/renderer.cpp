#include <memory>

#include "headers.hpp"
#include "renderer.hpp"
#include "mandelbrot.hpp"

Renderer::Renderer() : window(SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED)),
                       //  renderer(SDL_CreateRenderer(window, -1, 0 /*SDL_RENDERER_TARGETTEXTURE*/)),  // allows for rendering on textures.
                       canvas(SDL_CreateRGBSurfaceWithFormat(
                           0, winWidth, winHeight, 32, SDL_PIXELFORMAT_RGBA8888)),
                       canvasBuffer((Uint32 *)canvas->pixels) {
    // clear();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, 255);
    SDL_RenderClear(renderer);
}

void Renderer::renderCopy(SDL_Texture *tex, const SDL_Rect *src, const SDL_Rect *dst) {
    SDL_RenderCopy(renderer, tex, src, dst);
}

SDL_Texture *Renderer::createTexture(Uint32 format, int access, int w, int h) {
    return SDL_CreateTexture(renderer, format, access, w, h);
}

// returns a texture that was made from a surface
SDL_Texture *Renderer::CreateTextureFromSurface(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(renderer, surface);
}

// null means taht the target will be reset
void Renderer::changeRendrTarget(SDL_Texture *targetTex) {
    SDL_SetRenderTarget(renderer, targetTex);
}

void Renderer::drawPoint(int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer::renderMandelbrot(double scale, double xBound, double yBound) {
    Uint32 colour;

    double scaledX, scaledY = yBound;
    int linearPos = 0;

    SDL_LockSurface(canvas);
    for (int y = 0; y < winHeight; y++, scaledY += scale) {
        scaledX = xBound;
        for (int x = 0; x < winWidth; x++, scaledX += scale) {
            colour = mandelbrot::fn(scaledX, scaledY, SEARCH_LIMIT);

            canvasBuffer[linearPos++] = colour;
        }
    }
    SDL_UnlockSurface(canvas);
}

void Renderer::saveAsPng(const char *path) {
    IMG_SavePNG(window_surface, path);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::updateWindowSurfaceWithCanvas() {
    SDL_BlitSurface(canvas, NULL, window_surface, NULL);
    SDL_UpdateWindowSurface(window);
}

Renderer::~Renderer() {
    SDL_FreeSurface(canvas);
    SDL_FreeSurface(window_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
