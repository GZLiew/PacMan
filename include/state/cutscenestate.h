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

#define MAX_CICLE_COUNT_CUTSCENE 256

namespace State {
  class CutsceneState : public BaseState {
  public:
    CutsceneState(Application &app);
    ~CutsceneState();

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
    std::vector<Objects::Ghost> m_ghosts;
    Objects::Ready m_ready;

    void switchToPlayingState();
  };
}  // namespace State