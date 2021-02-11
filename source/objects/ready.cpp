#include <objects/ready.h>

#include <iostream>

Objects::Ready::Ready(std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({10 * 16, 16}, {20 * 16, .5 * 16}, {0.f, 0.f},
             Collision::Hitbox({0.0f, 0.0f}, {0.f, 0.f})),
      m_renderer(renderer) {}

void Objects::Ready::add(int amount) { this->m_amount += amount; }

void Objects::Ready::draw() {
  SDL_Rect hsQuad{150, 320, 160, 16};
  this->m_renderer->drawText("GET READY!", 16, hsQuad);
}