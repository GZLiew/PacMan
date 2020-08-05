#include <state/playingstate.h>

State::PlayingState::PlayingState(Application &app)
    : State::BaseState(app), m_pacman(app.renderer()) {
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

void State::PlayingState::update(float dt) { this->m_pacman.update(dt); }

void State::PlayingState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_pacman.draw();
}

void State::PlayingState::onOpen() {}