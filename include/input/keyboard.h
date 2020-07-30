#pragma once

#include <SDL.h>
#include <input.h>
#include <input/actions.h>

#include <algorithm>
#include <map>
#include <set>

#define SDL_KEY_COUNT 322

namespace Input {
  class Keyboard : public Input {
  public:
    Keyboard(std::map<Action, SDL_Keycode> mapping);

    void update(SDL_Event& e) override;

    bool isKeyDown(Action action) const override;
    bool keyReleased(Action action) const override;

  private:
    Action findByKey(const SDL_Keycode& key) const;

    std::set<SDL_Keycode> m_pushed_keys;
    std::map<Action, SDL_Keycode> m_key_mapping;
    Action m_last_released_key;
  };
}  // namespace Input