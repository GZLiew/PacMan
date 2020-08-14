#include <render/textrenderer.h>

Render::TextRenderer::TextRenderer(std::shared_ptr<SDL_Renderer> renderer) : m_renderer(renderer) {
  this->m_fonts = std::map<int, std::unique_ptr<TTF_Font, TTF_FontDeleter>>();
  this->m_fonts[6]  = std::unique_ptr<TTF_Font, TTF_FontDeleter>(TTF_OpenFont("resources/fonts/press-start-2p/PressStart2P-vaV7.ttf", 6));
  this->m_fonts[12] = std::unique_ptr<TTF_Font, TTF_FontDeleter>(TTF_OpenFont("resources/fonts/press-start-2p/PressStart2P-vaV7.ttf", 12));
  this->m_fonts[16] = std::unique_ptr<TTF_Font, TTF_FontDeleter>(TTF_OpenFont("resources/fonts/press-start-2p/PressStart2P-vaV7.ttf", 16));
  this->m_fonts[24] = std::unique_ptr<TTF_Font, TTF_FontDeleter>(TTF_OpenFont("resources/fonts/press-start-2p/PressStart2P-vaV7.ttf", 24));
  this->m_fonts[48] = std::unique_ptr<TTF_Font, TTF_FontDeleter>(TTF_OpenFont("resources/fonts/press-start-2p/PressStart2P-vaV7.ttf", 48));
}

void Render::TextRenderer::drawText(const std::string text, const int size, const SDL_Rect& pos) {
  std::shared_ptr<SDL_Surface> surf = 
    std::shared_ptr<SDL_Surface>(TTF_RenderUTF8_Blended(
                      this->m_fonts[size].get(), text.c_str(), white), [](SDL_Surface*s){ SDL_FreeSurface(s); });
  
  std::shared_ptr<SDL_Texture> txt =
    std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(
      this->m_renderer.get(),
      surf.get()
    ), [](SDL_Texture *t) { SDL_DestroyTexture(t); });
  SDL_RenderCopyEx(this->m_renderer.get(),
                  txt.get(),
                  NULL,
                  &pos, 
                  0,
                  NULL,
                  SDL_FLIP_NONE);
}