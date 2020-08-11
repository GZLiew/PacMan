#pragma once

#include <deleters.h>
#include <entity.h>
#include <render/masterrenderer.h>

#include <memory>

namespace Objects {
  class Points50 : public Entity {
  public:
    Points50(const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer);
    void eat();
    bool isEaten();
    void draw();

  private:
    bool m_eaten = false;
    std::unique_ptr<SDL_Texture, SDL_TextureDeleter> m_texture;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
  };
}  // namespace Objects