#pragma once

#include "basestate.h"
#include "../input/keyboard.h"
#include "../render/masterrenderer.h"

namespace State{
class PlayingState : public BaseState {
  public:
    PlayingState(Application &app);
    ~PlayingState();

    void handleEvent(SDL_Event &e) override;
    void handleInput() override;

    void update(float deltaTime) override;

    void render(Render::MasterRenderer &renderer) override;

    void onOpen() override;
  
  private:
    Input::Keyboard m_keyboard;
};
}