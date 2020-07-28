#pragma once

#include <SDL.h>
#include <config.h>
#include <input/keyboard.h>
#include <render/masterrenderer.h>
#include <state/basestate.h>
#include <state/playingstate.h>
#include <stdio.h>

#include <memory>
#include <vector>

class Application {
public:
  Application(const Config& config);
  ~Application();
  template <typename T, typename... Args> void pushState(Args&&... args) {
    this->m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    auto& s = m_states.back();
    s->onOpen();
  }
  void run_loop();
  Config get_config();

private:
  bool m_sdl_initialized = false;
  bool m_window_created = false;
  bool m_gl_initialized = false;
  const Config& m_config;

  SDL_GLContext m_gl_context;

  std::vector<std::unique_ptr<State::BaseState>> m_states;

  Render::MasterRenderer m_renderer;
  SDL_Window* m_window;
  SDL_Surface* m_basesurface;
};  // class Application
