#include <application.h>
#include <iostream>

Application::~Application() {
  if (this->m_sdl_initialized) {
    SDL_DestroyWindow(this->m_window);
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
    this->m_renderer = Render::MasterRenderer();

    // Push initial state
    this->pushState<State::PlayingState>(*this);
  }
}


void Application::run_loop() {
  SDL_Event e;
  while (!this->m_states.empty()) {
    auto &state = *this->m_states.back();
    state.handleInput();
    //state.update(0);

    state.render(this->m_renderer);
    this->m_renderer.finish_render(this->m_window);

    // Check input
    while(SDL_PollEvent(&e)){
      this->m_states.back()->handleEvent(e);
      switch(e.type){
        case SDL_QUIT:
          while(!this->m_states.empty()) this->m_states.pop_back();
          break;
        default:
          break;
      }
    }
  }
}

Config Application::get_config() { return this->m_config; }
