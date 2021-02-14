#pragma once

#include <application.h>
#include <audio/manager.h>
#include <input/keyboard.h>
#include <objects/ghost.h>
#include <objects/level.h>
#include <objects/pacman.h>
#include <objects/ready.h>
#include <render/masterrenderer.h>
#include <state/basestate.h>

#include <memory>

#define MAX_CICLE_COUNT_DEATH 128

namespace State {
  class DeathState : public BaseState {
  public:
    DeathState(Application &app, Objects::Level &level, Objects::Pacman &pacman,
               Objects::Score &score, std::vector<Objects::Ghost> ghosts);
    ~DeathState();

    void handleEvent(SDL_Event &e) override;
    void handleInput() override;
    void update(float dt) override;
    void render(std::shared_ptr<Render::MasterRenderer> renderer) override;
    void onOpen() override;
    void onSwitchBack() override;

  private:
    int cycleCount = 0;
    std::shared_ptr<Audio::Manager> m_audio_manager;
    Objects::Level m_level;
    Objects::Pacman m_pacman;
    Objects::Score m_score;
    std::vector<Objects::Ghost> m_ghosts;

    void switchToPlayingState();
  };
}  // namespace State