#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

namespace Utils {
  void showError(std::string msg);
  SDL_Surface* loadSDLSurface(const char* file);

  struct SDLWindowDeleter {
    inline void operator()(SDL_Window* window) {
      SDL_DestroyWindow(window);
    }
  };
}

