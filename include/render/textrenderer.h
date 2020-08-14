#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <memory>
#include <vector>

#include <deleters.h>

namespace Render {
  class TextRenderer {
  public:
    TextRenderer(std::shared_ptr<SDL_Renderer> renderer);
    void drawText(const std::string text, const int size, const SDL_Rect& pos);

  private:
    SDL_Color white = {255, 255, 255, 255};
    std::shared_ptr<SDL_Renderer> m_renderer;
    std::map<int, std::unique_ptr<TTF_Font, TTF_FontDeleter>> m_fonts; 
  };
}  // namespace Render