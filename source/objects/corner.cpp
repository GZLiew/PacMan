#include <objects/corner.h>

Objects::Corner::Corner(const glm::vec2& pos)
    : Entity({0.0f, 0.0f}, pos, {0.f, 0.f}, Collision::Hitbox({15.9f, 15.9f}, pos)) {
}