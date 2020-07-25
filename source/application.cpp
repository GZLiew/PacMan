#include <SDL.h>
#include <application.h>
#include <stdio.h>

Application::Application(const Config &config) : m_config(config) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return;
  }
  this->m_window
      = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         this->m_config.windowX, this->m_config.windowY, SDL_WINDOW_SHOWN);

  if (this->m_window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return;
  }

  this->m_basesurface = SDL_GetWindowSurface(this->m_window);
  SDL_FillRect(this->m_basesurface, NULL,
               SDL_MapRGB(this->m_basesurface->format, 0xFF, 0xFF, 0xFF));
}

void Application::run_loop() {
  SDL_UpdateWindowSurface(this->m_window);
  SDL_Delay(2000);
  SDL_DestroyWindow(this->m_window);
  SDL_Quit();
  return;
}

Config Application::get_config() { return this->m_config; }
