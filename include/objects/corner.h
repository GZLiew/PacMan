#pragma once

#include <entity.h>

namespace Objects {
  class Corner : public Entity {
  public:
    Corner(const glm::vec2& pos);
  };
}  // namespace Objects