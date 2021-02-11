#include <state/cutscenestate.h>

State::CutsceneState::CutsceneState(Application& app)
    : State::BaseState(app),
      m_audio_manager(app.audioManager()),
      m_pacman(app.renderer()),
      m_level({0.f, 0.f}, app.renderer()),
      m_ready(app.renderer()) {
  this->m_ghosts = std::vector<Objects::Ghost>();
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::BLINKY, app.renderer(), {13.5 * 16.f, 14 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::PINKY, app.renderer(), {15.5 * 16.f, 17 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::INKY, app.renderer(), {11.5 * 16.f, 17 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::CLYDE, app.renderer(), {13.5 * 16.f, 17 * 16.f}));
}

State::CutsceneState::~CutsceneState() {}

void State::CutsceneState::handleEvent(SDL_Event& e) {}

void State::CutsceneState::handleInput() {}

void State::CutsceneState::update(float dt) {
  this->cycleCount++;
  if (this->cycleCount % MAX_CICLE_COUNT == 0) {
    this->m_application.popState();
  }
}

void State::CutsceneState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_level.draw();
  this->m_ready.draw();
  this->m_pacman.draw();
  for (auto& ghost : this->m_ghosts) ghost.draw();
}

void State::CutsceneState::onOpen() { this->m_audio_manager->playSound("intro"); }