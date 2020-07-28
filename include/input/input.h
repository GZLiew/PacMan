#pragma once

#include <SDL.h>

#include <set>

#define SDL_KEY_COUNT 322

namespace Input {
  class Input {
  public:
    Input() {};
    virtual ~Input() = default;

    virtual void update(SDL_Event &e) = 0;

    virtual bool isKeyDown(SDL_Keycode key) const = 0;
    virtual bool keyReleased(SDL_Keycode key) const = 0;

  private:
    std::set<SDL_Keycode> m_pushed_keys;
    SDL_Keycode m_last_released_key;
  };
}  // namespace Input