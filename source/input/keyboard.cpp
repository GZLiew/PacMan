#include <input/keyboard.h>

Input::Keyboard::Keyboard() { std::fill(this->m_keys.begin(), this->m_keys.end(), false); }

void Input::Keyboard::update(SDL_Event &e) {
  if (!SDL_PollEvent(&e)) return;
  switch (e.type) {
    case SDL_KEYDOWN:
      this->m_last_released_key = e.key.keysym.sym;
      this->m_keys[e.key.keysym.sym] = true;
      break;
    case SDL_KEYUP:
      this->m_keys[e.key.keysym.sym] = false;
      break;
    default:
      break;
  }
}

bool Input::Keyboard::isKeyDown(SDL_Keycode key) const { return m_keys[key]; }

bool Input::Keyboard::keyReleased(SDL_Keycode key) const { return m_last_released_key == key; }