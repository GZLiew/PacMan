#pragma once

#include <config.h>
#include <render/masterrenderer.h>

#include <memory>
#include <vector>

class Application {
public:
  Application(const Config& config);
  ~Application();
  void run_loop();
  Config get_config();

private:
  const Config& m_config;
  Render::MasterRenderer* m_renderer;
  SDL_Window* m_window;
  SDL_Surface* m_basesurface;

};  // class Application
