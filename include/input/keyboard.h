#pragma once

#include <SDL.h>

#include <array>

#define SDL_KEY_COUNT 322

namespace Input {
  class Keyboard {
  public:
    Keyboard();

    void update(SDL_Event &e);

    bool isKeyDown(SDL_Keycode key) const;
    bool keyReleased(SDL_Keycode key) const;

  private:
    std::array<bool, SDL_KEY_COUNT> m_keys;
    SDL_Keycode m_last_released_key;
  };
}  // namespace Input