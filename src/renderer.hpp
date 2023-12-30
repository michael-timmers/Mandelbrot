#pragma once

namespace renderer {

// set up renderer and window
int init();

// clears the renderer
void clear();

void renderCopy(SDL_Texture* tex, const SDL_Rect* src, const SDL_Rect* dst);

SDL_Texture* createTexture(Uint32 format, int access, int w, int h);

// returns a texture that was made from a surface
SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

// changes the render target
void changeRendrTarget(SDL_Texture* targetTex = NULL);

void renderMandelbrot(double scale, double xOffset, double yOffset);

// presents the renderer
void present();

// destroys the variables
void kill();

}  // namespace renderer