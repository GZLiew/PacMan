#include <glm/vec2.hpp>

namespace Collision {
  struct Hitbox {
    Hitbox(const glm::vec2& dim, const glm::vec2& pos) : dim(dim), pos(pos){};
    bool collide(Hitbox& other) const;
    bool within(Hitbox& other) const;

    const glm::vec2 dim;
    glm::vec2 pos;
  };
}  // namespace Collision