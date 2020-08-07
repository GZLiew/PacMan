#pragma once

#include <deleters.h>
#include <entity.h>
#include <render/masterrenderer.h>

#include <memory>

namespace Objects {
  class Points10 : public Entity {
  public:
    Points10(const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer);
    void eat();
    void draw();

  private:
    bool eaten = false;
    std::unique_ptr<SDL_Texture, SDL_TextureDeleter> m_texture;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
  };
}  // namespace Objects