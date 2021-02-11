#pragma once

#include <deleters.h>
#include <entity.h>
#include <input.h>
#include <input/actions.h>
#include <objects/pacman.h>
#include <render/masterrenderer.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <utils.h>

#include <algorithm>
#include <memory>
#include <vector>

#define GHOST_ANIMATION_STATES 12

namespace Objects {
  enum GhostType { BLINKY, PINKY, INKY, CLYDE };

  class Ghost : public Entity {
  public:
    Ghost(GhostType t, std::shared_ptr<Render::MasterRenderer> renderer, const glm::vec2& pos);
    void update(float dt);
    void checkDirection(std::vector<Direction> directions);
    void setScare(bool s);

    void draw();

  private:
    void changeDirection(Direction dir);
    void updateVelocity(glm::vec2 vel);

    bool m_is_scared = false;
    GhostType m_type;
    Direction m_direction = NONE;
    std::vector<std::shared_ptr<SDL_Texture>> m_textures_none;
    std::vector<std::shared_ptr<SDL_Texture>> m_textures_down;
    std::vector<std::shared_ptr<SDL_Texture>> m_textures_left;
    std::vector<std::shared_ptr<SDL_Texture>> m_textures_right;
    std::vector<std::shared_ptr<SDL_Texture>> m_textures_up;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
    int m_animation_state = 0;
    float dt;
  };
}  // namespace Objects