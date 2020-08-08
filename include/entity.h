#pragma once
#include <collision/hitbox.h>

#include <glm/vec2.hpp>

struct Entity {
  Entity(const glm::vec2& dim, const glm::vec2& pos, const glm::vec2& vel,
         const Collision::Hitbox& hitbox)
      : dimension(dim), position(pos), velocity(vel), hitbox(hitbox) {}

  glm::vec2 dimension;
  glm::vec2 position;
  glm::vec2 velocity;
  Collision::Hitbox hitbox;
};