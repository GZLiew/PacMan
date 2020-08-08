#pragma once

#include <objects/pacman.h>
#include <entity.h>

namespace Objects {
  class Corner : public Entity {
  public:
    Corner(const glm::vec2& pos, std::vector<Direction> dir);
    std::vector<Direction> directions();

  private:
    std::vector<Direction> m_directions;
  };
}  // namespace Objects