#include <collision/hitbox.h>

bool Collision::Hitbox::collide(Hitbox &other) const {
  return pos.x <= other.pos.x + other.dim.x && pos.x + dim.x >= other.pos.x
         && pos.y <= other.pos.y + other.dim.y && pos.y + dim.y >= other.pos.y;
}

bool Collision::Hitbox::equal(Hitbox &other) const {
  return pos.x == other.pos.x &&
         pos.y == other.pos.y &&
         dim.x == other.dim.x &&
         dim.y == other.dim.y;
}