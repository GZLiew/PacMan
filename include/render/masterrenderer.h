#pragma once
#include <SDL.h>
#include <memory>

namespace Render {
  class MasterRenderer {
  public:
    MasterRenderer(std::shared_ptr<SDL_Surface> baseSurface);
    void finishRender(SDL_Window* window);
    void clearSurface();
    std::shared_ptr<SDL_Surface> getBaseSurface();
    
  private:
    std::shared_ptr<SDL_Surface> m_base_surface;
  };
}  // namespace Render