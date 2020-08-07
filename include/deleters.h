#pragma once
#include <SDL.h>

struct SDL_WindowDeleter {
  inline void operator()(SDL_Window* window) { SDL_DestroyWindow(window); }
};

struct SDL_TextureDeleter {
  inline void operator()(SDL_Texture* t) { SDL_DestroyTexture(t); }
};