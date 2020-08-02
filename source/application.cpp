#include <application.h>

Application::~Application() {
  if (this->m_gl_initialized) SDL_GL_DeleteContext(this->m_gl_context);
  if (this->m_sdl_initialized) {
    if (this->m_window_created) this->m_window.reset();
    SDL_Quit();
  }
  this->m_states.clear();
  this->m_renderer.reset();
  this->m_window.reset();
  this->m_basesurface.reset();
}

Application::Application(const Config &config) : m_config(config) {
  // Set openGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Init SDL components
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    Utils::showError("SDL failed to initialize: ");
    this->m_sdl_initialized = false;
  } else {
    this->m_window = std::unique_ptr<SDL_Window, Utils::SDLWindowDeleter>(SDL_CreateWindow(
        "PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_config.windowX,
        this->m_config.windowY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));

    if (this->m_window == NULL) {
      Utils::showError("could not create window: %s\n");
      this->m_sdl_initialized = false;
      this->m_window_created = false;
    } else {
      this->m_window_created = true;

      this->m_gl_context = SDL_GL_CreateContext(this->m_window.get());
      if (this->m_gl_context == nullptr) {
        Utils::showError("OpenGL context could not be created: ");
        return;
      } else {
      }
      this->m_gl_initialized = true;
    }

    this->m_basesurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface(this->m_window.get()));
    SDL_FillRect(this->m_basesurface.get(), NULL,
                 SDL_MapRGB(this->m_basesurface->format, 0xFF, 0xFF, 0xFF));

    this->m_sdl_initialized = true;

    // Init renderer
    this->m_renderer = std::shared_ptr<Render::MasterRenderer>(new Render::MasterRenderer());

    // Push initial state
    this->pushState<State::PlayingState>(*this);
  }
}

void Application::run_loop() {
  SDL_Event e;
  while (!this->m_states.empty()) {
    auto &state = *this->m_states.back();
    state.handleInput();
    // state.update(0);

    state.render(this->m_renderer);
    this->m_renderer->finish_render(this->m_window.get());

    // Check input
    while (SDL_PollEvent(&e)) {
      this->m_states.back()->handleEvent(e);
      switch (e.type) {
        case SDL_QUIT:
          while (!this->m_states.empty()) this->m_states.pop_back();
          break;
        default:
          break;
      }
    }
  }
}

Config Application::get_config() { return this->m_config; }
