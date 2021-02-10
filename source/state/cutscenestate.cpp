#include <state/cutscenestate.h>

State::CutsceneState::CutsceneState(Application& app) : State::BaseState(app),
      m_audio_manager(app.audioManager()),
      m_pacman(app.renderer()),
      m_level({0.f, 0.f}, app.renderer()) {
  this->m_ghosts = std::vector<Objects::Ghost>();
  this->m_ghosts.push_back(Objects::Ghost(Objects::GhostType::BLINKY, app.renderer()));
  this->m_ghosts.push_back(Objects::Ghost(Objects::GhostType::PINKY, app.renderer()));
  this->m_ghosts.push_back(Objects::Ghost(Objects::GhostType::INKY, app.renderer()));
  this->m_ghosts.push_back(Objects::Ghost(Objects::GhostType::CLYDE, app.renderer()));
}

State::CutsceneState::~CutsceneState() { }

void State::CutsceneState::handleEvent(SDL_Event& e) { }

void State::CutsceneState::handleInput() { }

void State::CutsceneState::update(float dt) { }

void State::CutsceneState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_level.draw();
  this->m_pacman.draw();
  for (auto& ghost : this->m_ghosts) ghost.draw();
}

void State::CutsceneState::onOpen() { }