#pragma once

#include <SDL.h>
#include <config.h>
#include <input/keyboard.h>
#include <render/masterrenderer.h>
#include <stdio.h>

#include <memory>
#include <vector>

class Application {
public:
  Application(const Config& config);
  ~Application();
  void run_loop();
  Config get_config();

private:
  bool m_sdl_initialized = false;
  const Config& m_config;

  Render::MasterRenderer* m_renderer;
  SDL_Window* m_window;
  SDL_Surface* m_basesurface;

  Input::Keyboard* m_keyboard;

};  // class Application
