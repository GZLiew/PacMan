#pragma once
#include <collision/hitbox.h>

#include <glm/vec2.hpp>

struct Entity {
  Entity(const glm::vec2& dim, const glm::vec2& pos, const glm::vec2& vel)
      : hitbox(dim, pos), velocity(vel) {}

  Collision::Hitbox hitbox;
  glm::vec2 velocity;
};