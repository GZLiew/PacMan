#pragma once
#include <glm/vec2.hpp>

struct Entity {
    Entity();

    glm::vec2 position;
    glm::vec3 velocity;
}