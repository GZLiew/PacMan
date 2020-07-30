#pragma once

#include <SDL.h>
#include <input/actions.h>

#define SDL_KEY_COUNT 322

namespace Input {
  class Input {
  public:
    Input(){};
    virtual ~Input() = default;

    virtual void update(SDL_Event &e) = 0;

    virtual bool isKeyDown(Action action) const = 0;
    virtual bool keyReleased(Action action) const = 0;
  };
}  // namespace Input