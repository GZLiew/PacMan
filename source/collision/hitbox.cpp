#include <collision/hitbox.h>

void Collision::Hitbox::update(glm::vec2 pos) { this->pos = pos; }

bool Collision::Hitbox::collide(Hitbox &other) const {
  return pos.x <= other.pos.x + other.dim.x/4 && pos.x + dim.x/4 >= other.pos.x
         && pos.y <= other.pos.y + other.dim.y/4 && pos.y + dim.y/4 >= other.pos.y;
}