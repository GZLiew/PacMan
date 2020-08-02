#pragma once

#include <SDL.h>

#include <iostream>
#include <string>

namespace Utils {
  void showError(std::string msg);
  SDL_Surface* loadSDLSurface(const char* file);

  struct SDLWindowDeleter {
    inline void operator()(SDL_Window* window) { SDL_DestroyWindow(window); }
  };
}  // namespace Utils
