#pragma once
#include <SDL.h>
#include <render/textrenderer.h>
#include <utils.h>

#include <memory>

namespace Render {
  class MasterRenderer {
  public:
    MasterRenderer(SDL_Renderer* renderer);
    void finishRender();
    void clearSurface();
    void drawText(const std::string text, const int size, const SDL_Rect& pos);
    std::shared_ptr<SDL_Renderer> renderer();

  private:
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::unique_ptr<TextRenderer> m_text_renderer;
  };
}  // namespace Render