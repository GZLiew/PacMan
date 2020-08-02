#include <utils.h>

void Utils::showError(std::string msg) {
  msg.append(SDL_GetError());
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", msg.c_str(), nullptr);
}

SDL_Surface* Utils::loadSDLSurface(const char* file) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(file);
  if(loadedSurface == NULL){
    showError("Could not load file: " + std::string(file));
  }
  return loadedSurface;
}