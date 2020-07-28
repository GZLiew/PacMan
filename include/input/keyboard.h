#pragma once

#include <SDL.h>
#include <input.h>

#include <set>

#define SDL_KEY_COUNT 322

namespace Input {
  class Keyboard : public Input {
  public:
    Keyboard();

    void update(SDL_Event &e) override;

    bool isKeyDown(SDL_Keycode key) const override;
    bool keyReleased(SDL_Keycode key) const override;

  private:
    std::set<SDL_Keycode> m_pushed_keys;
    SDL_Keycode m_last_released_key;
  };
}  // namespace Input