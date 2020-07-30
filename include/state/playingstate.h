#pragma once

#include <input/keyboard.h>
#include <objects/pacman.h>
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

    void update(float deltaTime) override;

    void render(std::shared_ptr<Render::MasterRenderer> renderer) override;

    void onOpen() override;

  private:
    std::shared_ptr<Input::Input> m_input;
    Objects::Pacman m_pacman;
  };
}  // namespace State