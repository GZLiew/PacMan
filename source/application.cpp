#include <application.h>

#include <iostream>

void showError(std::string msg) {
  msg.append(SDL_GetError());
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", msg.c_str(), nullptr);
}

Application::~Application() {
  if (this->m_gl_initialized) SDL_GL_DeleteContext(this->m_gl_context);
  if (this->m_sdl_initialized) {
    if (this->m_window_created) SDL_DestroyWindow(this->m_window);
    SDL_Quit();
  }
  this->m_renderer.reset();
}

Application::Application(const Config &config) : m_config(config) {
  // Set openGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Init SDL components
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    showError("SDL failed to initialize: ");
    this->m_sdl_initialized = false;
  } else {
    this->m_window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      this->m_config.windowX, this->m_config.windowY,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (this->m_window == NULL) {
      showError("could not create window: %s\n");
      this->m_sdl_initialized = false;
      this->m_window_created = false;
    } else {
      this->m_window_created = true;

      this->m_gl_context = SDL_GL_CreateContext(this->m_window);
      if (this->m_gl_context == nullptr) {
        showError("OpenGL context could not be created: ");
        return;
      } else {
      }
      this->m_gl_initialized = true;
    }

    this->m_basesurface = SDL_GetWindowSurface(this->m_window);
    SDL_FillRect(this->m_basesurface, NULL,
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
    this->m_renderer->finish_render(this->m_window);

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
