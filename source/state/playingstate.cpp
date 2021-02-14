#include <state/playingstate.h>

State::PlayingState::PlayingState(Application& app)
    : State::BaseState(app),
      m_audio_manager(app.audioManager()),
      m_pacman(app.renderer()),
      m_level({0.f, 0.f}, app.renderer()),
      m_score(app.renderer()) {
  this->m_ghosts = std::vector<Objects::Ghost>();
  this->resetLevel(app);
}

State::PlayingState::~PlayingState() { this->m_input.reset(); }

void State::PlayingState::handleEvent(SDL_Event& e) { this->m_input->update(e); }

void State::PlayingState::handleInput() { this->m_pacman.handleInput(this->m_input); }

void State::PlayingState::update(float dt) {
  // Check pacman and ghosts corner collision and direction
  for (auto corner : this->m_level.getCorners()) {
    if (corner->hitbox.equal(this->m_pacman.hitbox)) {
      this->m_pacman.checkDirection(corner->directions());
    }
    for (auto& ghost : this->m_ghosts) {
      if (corner->hitbox.equal(ghost.hitbox)) {
        ghost.checkDirection(corner->directions());
      }
      if (ghost.hitbox.collide(this->m_pacman.hitbox)) {
        switch (ghost.getState()) {
          case Objects::GhostState::VULNERABLE:
            ghost.setState(Objects::GhostState::DEAD);
            break;
          case Objects::GhostState::CHASING:
            this->switchToDeathState();
            break;
          case Objects::GhostState::BLOCKED:
            this->switchToDeathState();
            break;
          case Objects::GhostState::DEAD:
            break;
        }
      }
    }
  }

  // Check if pacman eat pellts
  for (auto pelet : this->m_level.getPoints10()) {
    if (!pelet->isEaten() && pelet->hitbox.collide(this->m_pacman.hitbox)) {
      pelet->eat();
      this->peletsEaten++;
      this->m_score.add(10);
      if (this->peletsEaten % 2 == 0)
        this->m_audio_manager->playSound("munch_a");
      else
        this->m_audio_manager->playSound("munch_b");
    }
  }
  for (auto pelet50 : this->m_level.getPoints50()) {
    if (!pelet50->isEaten() && pelet50->hitbox.collide(this->m_pacman.hitbox)) {
      pelet50->eat();
      this->peletsEaten++;
      this->m_score.add(50);
      this->m_audio_manager->playSound("large_pellet");
      for (auto& ghost : this->m_ghosts) {
        ghost.setState(Objects::GhostState::VULNERABLE);
      }
    }
  }

  // Update moving characters
  this->m_pacman.update(dt);
  for (auto& ghost : this->m_ghosts) {
    ghost.update(dt);
  }

  // Play default level sounds
  if (this->cycleCount % 32 == 0) this->m_audio_manager->playSound("siren");

  this->cycleCount++;
  if (this->cycleCount % MAX_CICLE_COUNT_PLAYING == 0) this->cycleCount = 0;
}

void State::PlayingState::render(std::shared_ptr<Render::MasterRenderer> renderer) {
  renderer->clearSurface();
  this->m_level.draw();
  this->m_score.draw();
  this->m_pacman.draw();
  for (auto& ghost : this->m_ghosts) ghost.draw();
}

void State::PlayingState::onOpen() {}

void State::PlayingState::onSwitchBack() {
  if (this->deathStateSwitched) {
    this->resetLevel(this->m_application);
  }

  this->deathStateSwitched = false;
}

void State::PlayingState::switchToDeathState() {
  if (!this->deathStateSwitched) {
    this->m_application.pushState<State::DeathState>(this->m_application, this->m_level,
                                                     this->m_pacman, this->m_score, this->m_ghosts);
    this->deathStateSwitched = true;
  }
}

void State::PlayingState::resetLevel(Application& app) {
  this->m_ghosts.clear();
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::BLINKY, app.renderer(), {13.5 * 16.f, 14 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::PINKY, app.renderer(), {13.5 * 16.f, 17 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::INKY, app.renderer(), {13.5 * 16.f, 17 * 16.f}));
  this->m_ghosts.push_back(
      Objects::Ghost(Objects::GhostType::CLYDE, app.renderer(), {13.5 * 16.f, 17 * 16.f}));

  this->m_input.reset();
  this->m_input
      = std::shared_ptr<Input::Input>(new Input::Keyboard({{Input::Action::CONFIRM, SDLK_RETURN},
                                                           {Input::Action::DECLINE, SDLK_ESCAPE},
                                                           {Input::Action::UP, SDLK_UP},
                                                           {Input::Action::DOWN, SDLK_DOWN},
                                                           {Input::Action::LEFT, SDLK_LEFT},
                                                           {Input::Action::RIGHT, SDLK_RIGHT}}));

  this->m_pacman.reset();
}