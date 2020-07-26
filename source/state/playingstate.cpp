#include <state/playingstate.h>

State::PlayingState::PlayingState(Application &app) : State::BaseState(app) {
  m_keyboard = Input::Keyboard();
}

State::PlayingState::~PlayingState(){}

void State::PlayingState::handleEvent(SDL_Event &e) {
  m_keyboard.update(e);
}

void State::PlayingState::handleInput() {
}

void State::PlayingState::update(float deltaTime){
}

void State::PlayingState::render(Render::MasterRenderer &renderer) {
  renderer.draw_characters();
}

void State::PlayingState::onOpen() {
  
}