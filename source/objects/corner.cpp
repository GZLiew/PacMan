#include <objects/corner.h>

Objects::Corner::Corner(const glm::vec2& pos, std::vector<Direction> dir)
    : Entity({0.0f, 0.0f}, pos, {0.f, 0.f}, Collision::Hitbox({16.f, 16.f}, pos)),
      m_directions(dir) {}

std::vector<Objects::Direction> Objects::Corner::directions() { return this->m_directions; }