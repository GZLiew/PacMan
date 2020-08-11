#include <objects/score.h>

Objects::Score::Score(std::shared_ptr<Render::MasterRenderer> renderer)
  : Entity({32.0f, 32.0f}, {13.5 * 16.f - 8, 26 * 16.f - 8}, {0.f, 0.f},
      Collision::Hitbox({16.0f, 16.0f}, {13.5 * 16.f, 26 * 16.f})),
    m_renderer(renderer) {
}

void Objects::Score::add(int amount) { this->m_amount += amount; }

void Objects::Score::draw() {
  //TODO: implement draw function
}  