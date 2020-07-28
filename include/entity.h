#pragma once
#include <collision/hitbox.h>

#include <glm/vec2.hpp>

struct Entity {
  Entity(const glm::vec2 &pos, const glm::vec2 &vel) : position(pos), velocity(vel) {}

  glm::vec2 position;
  glm::vec2 velocity;
  Collision::Hitbox hitbox;
};