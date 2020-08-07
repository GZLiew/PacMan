#pragma once

#include <deleters.h>
#include <utils.h>
#include <entity.h>
#include <render/masterrenderer.h>

#include <memory>

namespace Objects {
  enum Type { 
    CORNER_DOUBLE =   10,
    CORNER_SHARP =    20,
    CORNER_SINGLE =   30,
    CORNER_SPECIAL =  40,
    WALL_DOUBLE =     50, 
    WALL_SINGLE =     60,

    O_RIGHT =         0, 
    O_UP =            1,
    O_DOWN =          2,
    O_LEFT =          3,
    HORIZONTAL =      4,
    VERTICAL =        5,
    HORIZONTAL_UP =   6,
    HORIZONTAL_DOWN = 7, 
    VERTICAL_RIGHT =  8,
    VERTICAL_LEFT =   9
  };

  class Wall : public Entity {
  public:
    Wall(Type t, const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer);
    void draw();

  private:
    Type m_type;
    double m_degree = 0;
    SDL_RendererFlip m_flip_type = SDL_FLIP_NONE;
    std::unique_ptr<SDL_Texture, SDL_TextureDeleter> m_texture;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
  };
}  // namespace Objects