#pragma once

#include <SDL.h>

#include <iostream>
#include <string>

namespace Utils {
  void showError(std::string msg);
  SDL_Surface* loadSDLSurface(const char* file);
  SDL_Texture* loadSDLTexture(SDL_Renderer* renderer, const char* file);
}  // namespace Utils
