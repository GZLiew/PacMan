#pragma once

#include <application.h>
#include <input/keyboard.h>
#include <objects/level.h>
#include <objects/pacman.h>
#include <objects/ghost.h>
#include <objects/score.h>
#include <render/masterrenderer.h>
#include <state/basestate.h>

#include <memory>

namespace State {
  class PlayingState : public BaseState {
  public:
    PlayingState(Application &app);
    ~PlayingState();

    void handleEvent(SDL_Event &e) override;
    void handleInput() override;

    void update(float dt) override;

    void render(std::shared_ptr<Render::MasterRenderer> renderer) override;

    void onOpen() override;

  private:
    std::shared_ptr<Input::Input> m_input;
    Objects::Level m_level;
    Objects::Pacman m_pacman;
    Objects::Score m_score;
    std::vector<Objects::Ghost> m_ghosts;
  };
}  // namespace State