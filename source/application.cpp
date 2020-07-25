#include <SDL.h>
#include <application.h>
#include <stdio.h>

Application::~Application() {
  if (this->m_sdl_initialized) {
    SDL_DestroyWindow(this->m_window);
    delete this->m_renderer;
    delete this->m_basesurface;
    SDL_Quit();
  }
}

Application::Application(const Config &config) : m_config(config) {
  // Init SDL components
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    this->m_sdl_initialized = false;
  } else {
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

    this->m_sdl_initialized = true;

    // Init renderer
    this->m_renderer = new Render::MasterRenderer();
  }
}

void Application::run_loop() {
  this->m_renderer->draw_characters();
  this->m_renderer->draw_hud();
  this->m_renderer->draw_points();
  this->m_renderer->draw_walls();
  this->m_renderer->finish_render(this->m_window);
}

Config Application::get_config() { return this->m_config; }
