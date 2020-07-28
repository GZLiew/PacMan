#include <collision/hitbox.h>


void Collision::Hitbox::update(glm::vec2 pos) {
    this->pos = pos;
}

bool Collision::Hitbox::collide(Hitbox &other) const {
    return
        pos.x <= other.pos.x + other.dim.x &&
        pos.x + dim.x >= other.pos.x &&
        pos.y <= other.pos.y + other.dim.y &&
        pos.y + dim.y >= other.pos.y;
}