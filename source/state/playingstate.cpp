#include <state/playingstate.h>

State::PlayingState::PlayingState(Application &app)
    : State::BaseState(app), m_pacman(app.renderer()), m_level({0.f, 0.f}, app.renderer()), m_score(app.renderer()) {
  this->m_input
      = std::shared_ptr<Input::Input>(new Input::Keyboard({{Input::Action::CONFIRM, SDLK_RETURN},
                                                           {Input::Action::DECLINE, SDLK_ESCAPE},
                                                           {Input::Action::UP, SDLK_UP},
                                                           {Input::Action::DOWN, SDLK_DOWN},
                                                           {Input::Action::LEFT, SDLK_LEFT},
                                                           {Input::Action::RIGHT, SDLK_RIGHT}}));
}

State::PlayingState::~PlayingState() { this->m_input.reset(); }

void State::PlayingState::handleEvent(SDL_Event &e) { this->m_input->update(e); }

void State::PlayingState::handleInput() { this->m_pacman.handleInput(this->m_input); }

void State::PlayingState::update(float dt) {
  for (auto corner : this->m_level.getCorners()) {
    if (corner->hitbox.equal(this->m_pacman.hitbox))
      this->m_pacman.checkDirection(corner->directions());
  }
  for (auto pelet : this->m_level.getPoints10()) {
    if (!pelet->isEaten() && pelet->hitbox.collide(this->m_pacman.hitbox)) {
      pelet->eat();
      this->m_score.add(10);
    }
  }
  for (auto pelet50 : this->m_level.getPoints50()) {
    if (!pelet50->isEaten() && pelet50->hitbox.collide(this->m_pacman.hitbox)) {
      pelet50->eat();
      this->m_score.add(50);
    }
  }
  this->m_pacman.update(dt);
}

void State::PlayingState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_level.draw();
  this->m_pacman.draw();
  this->m_score.draw();
}

void State::PlayingState::onOpen() {}