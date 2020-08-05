#include <render/masterrenderer.h>

Render::MasterRenderer::MasterRenderer(SDL_Surface* baseSurface, SDL_Renderer* renderer)
    : m_base_surface(baseSurface),
      m_renderer(renderer, [](SDL_Renderer* t) { SDL_DestroyRenderer(t); }) {}

void Render::MasterRenderer::finishRender() { SDL_RenderPresent(this->m_renderer.get()); }

void Render::MasterRenderer::clearSurface() {
  SDL_SetRenderDrawColor(this->m_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(this->m_renderer.get());
}

std::shared_ptr<SDL_Surface> Render::MasterRenderer::baseSurface() { return this->m_base_surface; }

std::shared_ptr<SDL_Renderer> Render::MasterRenderer::renderer() { return this->m_renderer; }