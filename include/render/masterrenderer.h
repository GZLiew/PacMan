#pragma once
#include <SDL.h>
#include <utils.h>

#include <memory>

namespace Render {
  class MasterRenderer {
  public:
    MasterRenderer(SDL_Renderer* renderer);
    void finishRender();
    void clearSurface();
    std::shared_ptr<SDL_Renderer> renderer();

  private:
    std::shared_ptr<SDL_Renderer> m_renderer;
  };
}  // namespace Render