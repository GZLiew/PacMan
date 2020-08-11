#include <objects/points50.h>

Objects::Points50::Points50(const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({16.0f, 16.0f}, pos, {0.f, 0.f},
             Collision::Hitbox({8.0f, 8.0f}, pos + glm::vec2{4, 4})),
      m_renderer(renderer) {
  this->m_texture = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(
      Utils::loadSDLTexture(renderer->renderer().get(), "resources/score/50pts.bmp"));
}

void Objects::Points50::eat() { this->m_eaten = true; }

bool Objects::Points50::isEaten() { return this->m_eaten; }

void Objects::Points50::draw() {
  if (this->m_eaten) return;

  SDL_Rect renderQuad{(int)this->position.x, (int)this->position.y, (int)this->dimension.x,
                      (int)this->dimension.y};
  SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_texture.get(), NULL, &renderQuad, 0,
                   NULL, SDL_FLIP_NONE);
}