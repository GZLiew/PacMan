#pragma once

#include <SDL.h>

#include <set>

#define SDL_KEY_COUNT 322

namespace Input {
  class Keyboard {
  public:
    Keyboard();

    void update(SDL_Event &e);

    bool isKeyDown(SDL_Keycode key) const;
    bool keyReleased(SDL_Keycode key) const;

  private:
    std::set<SDL_Keycode> m_pushed_keys;
    SDL_Keycode m_last_released_key;
  };
}  // namespace Input