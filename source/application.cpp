#include <application.h>

Application::Application(const Config& config) : m_config(config) {
  // Set openGL attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Init SDL and GL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    Utils::showError("SDL failed to initialize: ");
    this->m_sdl_initialized = false;
  } else {
    this->m_window = std::unique_ptr<SDL_Window, SDL_WindowDeleter>(SDL_CreateWindow(
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
      }
      this->m_gl_initialized = true;
      this->m_sdl_initialized = true;
    }

    // Init TTF
    TTF_Init();
    if (TTF_Init() == -1) {
      Utils::showError("SDL failed to initialize: ");
      this->m_ttf_initialized = false;
    } else {
      this->m_ttf_initialized = true;
    }

    // Init audio
    this->m_audio_manager = std::shared_ptr<Audio::Manager>(new Audio::Manager());

    SDL_Renderer* render = SDL_CreateRenderer(this->m_window.get(), -1,
                                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Init renderer
    this->m_renderer = std::shared_ptr<Render::MasterRenderer>(new Render::MasterRenderer(render));

    // Push initial state
    this->pushState<State::CutsceneState>(*this);
  }
}

Application::~Application() {
  if (this->m_ttf_initialized) {
    TTF_Quit();
  }
  if (this->m_gl_initialized) SDL_GL_DeleteContext(this->m_gl_context);
  if (this->m_sdl_initialized) {
    if (this->m_window_created) this->m_window.reset();
    SDL_Quit();
  }
  this->m_states.clear();
  this->m_renderer.reset();
  this->m_window.reset();
}

void Application::runLoop() {
  SDL_Event e;
  while (!this->m_states.empty()) {
    this->lockFps();

    auto& state = *this->m_states.back();
    state.handleInput();
    state.update(this->m_config.dt);

    state.render(this->m_renderer);
    this->m_renderer->finishRender();

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

Config Application::getConfig() { return this->m_config; }

std::shared_ptr<Render::MasterRenderer> Application::renderer() { return this->m_renderer; }

std::shared_ptr<Audio::Manager> Application::audioManager() { return this->m_audio_manager; }

void Application::lockFps() {
  double dt = SDL_GetTicks();
  dt = SDL_GetTicks() - dt;

  if (dt < 1000 / this->m_config.frameRate) {
    SDL_Delay((1000 / this->m_config.frameRate) - dt);
  }
}