#include <render/masterrenderer.h>

Render::MasterRenderer::MasterRenderer(std::shared_ptr<SDL_Surface> baseSurface) : m_base_surface(baseSurface) {}

void Render::MasterRenderer::finishRender(SDL_Window* window) { 
  SDL_UpdateWindowSurface(window);
}

void Render::MasterRenderer::clearSurface(){
  SDL_FillRect(this->m_base_surface.get(), NULL, SDL_MapRGB(this->m_base_surface->format, 0x00, 0x00, 0x00));
}

std::shared_ptr<SDL_Surface> Render::MasterRenderer::getBaseSurface() {
  return this->m_base_surface;
}
