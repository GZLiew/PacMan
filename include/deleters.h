#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

struct SDL_WindowDeleter {
  inline void operator()(SDL_Window* window) { SDL_DestroyWindow(window); }
};

struct SDL_TextureDeleter {
  inline void operator()(SDL_Texture* t) { SDL_DestroyTexture(t); }
};

struct TTF_FontDeleter {
  inline void operator()(TTF_Font* f) { TTF_CloseFont(f); }
};

struct Mixer_ChunkDeleter {
  inline void operator()(Mix_Chunk* c) { Mix_FreeChunk(c); }
};