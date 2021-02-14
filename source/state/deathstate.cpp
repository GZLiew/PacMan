#include <state/deathstate.h>

State::DeathState::DeathState(Application &app, Objects::Level &level, Objects::Pacman &pacman,
                              Objects::Score &score, std::vector<Objects::Ghost> ghosts)
    : State::BaseState(app),
      m_audio_manager(app.audioManager()),
      m_pacman(pacman),
      m_level(level),
      m_ghosts(ghosts),
      m_score(score) {}

State::DeathState::~DeathState() {}

void State::DeathState::handleEvent(SDL_Event &e) {}

void State::DeathState::handleInput() {}

void State::DeathState::update(float dt) {
  this->cycleCount++;
  this->m_pacman.update(dt);
  if (this->cycleCount == MAX_CICLE_COUNT_DEATH) {
    this->switchToPlayingState();
  }
}

void State::DeathState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_level.draw();
  this->m_score.draw();
  this->m_pacman.draw();
  for (auto &ghost : this->m_ghosts) ghost.draw();
}

void State::DeathState::onOpen() {
  this->m_audio_manager->playSound("death");
  this->m_pacman.kill();
}

void State::DeathState::onSwitchBack() {}

void State::DeathState::switchToPlayingState() { this->m_application.popState(); }