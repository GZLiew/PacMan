#include <render/masterrenderer.h>

Render::MasterRenderer::MasterRenderer(SDL_Renderer* renderer)
    : m_renderer(renderer, [](SDL_Renderer* t) { SDL_DestroyRenderer(t); }) {
  this->m_text_renderer = std::unique_ptr<TextRenderer>(new TextRenderer(m_renderer));
}

void Render::MasterRenderer::finishRender() { SDL_RenderPresent(this->m_renderer.get()); }

void Render::MasterRenderer::clearSurface() {
  SDL_SetRenderDrawColor(this->m_renderer.get(), 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(this->m_renderer.get());
}

void Render::MasterRenderer::drawText(const std::string text, const int size, const SDL_Rect& pos) {
  this->m_text_renderer->drawText(text, size, pos);
}

std::shared_ptr<SDL_Renderer> Render::MasterRenderer::renderer() { return this->m_renderer; }