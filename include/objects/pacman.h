#pragma once

#include <entity.h>
#include <input.h>
#include <input/actions.h>

#include <memory>

namespace Objects {
  enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

  class Pacman : public Entity {
  public:
    Pacman();
    void handleInput(std::shared_ptr<Input::Input> input);
    void update(float dt);

    void draw();

  private:
    Direction m_next_direction = NONE;
    float dt;
  };
}  // namespace Objects