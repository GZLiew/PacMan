#include <utils.h>

void Utils::showError(std::string msg) {
  msg.append(SDL_GetError());
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", msg.c_str(), nullptr);
}

SDL_Surface* Utils::loadSDLSurface(const char* file) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(file);
  if (loadedSurface == NULL) {
    showError("");
  }
  return loadedSurface;
}

SDL_Texture* Utils::loadSDLTexture(SDL_Renderer* renderer, const char* file) {
  return SDL_CreateTextureFromSurface(renderer, loadSDLSurface(file));
}
