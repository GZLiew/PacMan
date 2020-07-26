#pragma once

#include <SDL.h>
#include "../render/masterrenderer.h"

class Application;
class MasterRenderer;

namespace State{
class BaseState {
  public:
    BaseState(Application &app) : m_application(&app) {}
    virtual ~BaseState() = default;

    virtual void handleEvent(SDL_Event &e) = 0;
    virtual void handleInput() = 0;

   virtual void update(float deltaTime) = 0;

    virtual void render(Render::MasterRenderer &renderer) = 0;

    virtual void onOpen() = 0;

  private:
    Application *m_application;
};
}