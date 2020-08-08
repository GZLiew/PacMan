#include <collision/hitbox.h>

bool Collision::Hitbox::collide(Hitbox &other) const {
  return pos.x <= other.pos.x + other.dim.x && pos.x + dim.x >= other.pos.x
         && pos.y <= other.pos.y + other.dim.y && pos.y + dim.y >= other.pos.y;
}

bool Collision::Hitbox::within(Hitbox &other) const {
  return (pos.x + dim.x) - other.pos.x >=0 && (other.pos.x + other.dim.x) - pos.x >= 0
          && (pos.y + dim.y) - other.pos.y >=0 && (other.pos.y + other.dim.y) - pos.y >= 0;
}