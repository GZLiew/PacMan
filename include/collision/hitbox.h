#include <glm/vec2.hpp>

namespace Collision {
  struct Hitbox {
    Hitbox(const glm::vec2& dim, const glm::vec2& pos) : dim(dim), pos(pos){};
    void update(glm::vec2 pos);
    bool collide(Hitbox& other) const;

    const glm::vec2 dim;
    glm::vec2 pos;
  };
}  // namespace Collision