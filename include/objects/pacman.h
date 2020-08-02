#pragma once

#include <entity.h>
#include <input.h>
#include <input/actions.h>
#include <utils.h>

#include <memory>
#include <vector>

namespace Objects {
  enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

  class Pacman : public Entity {
  public:
    Pacman();
    void handleInput(std::shared_ptr<Input::Input> input);
    void update(float dt);

    void draw(std::shared_ptr<SDL_Surface> base);

  private:
    Direction m_direction = RIGHT;
    Direction m_next_direction = NONE;
    std::vector<std::unique_ptr<SDL_Surface>> m_sprites;
    int m_animation_state = 0;
    float dt;
  };
}  // namespace Objects