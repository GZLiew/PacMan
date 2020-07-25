#pragma once

#include <config.h>
#include <render/masterrenderer.h>

#include <memory>
#include <vector>

class Application {
public:
  Application(const Config& config);
  void run_loop();
  Config get_config();

private:
  // Render::MasterRenderer &m_renderer;
  const Config& m_config;
  SDL_Window* m_window;
  SDL_Surface* m_basesurface;

};  // class Application
