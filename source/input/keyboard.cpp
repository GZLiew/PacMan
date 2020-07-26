#include <input/keyboard.h>

Input::Keyboard::Keyboard() { this->m_pushed_keys = std::set<SDL_Keycode>();}

void Input::Keyboard::update(SDL_Event &e) {
  switch (e.type) {
    case SDL_KEYDOWN:
      this->m_last_released_key = e.key.keysym.sym;
      this->m_pushed_keys.insert(e.key.keysym.sym);
      break;
    case SDL_KEYUP:
      this->m_pushed_keys.erase(e.key.keysym.sym);
      break;
    default:
      break;
  }
}

bool Input::Keyboard::isKeyDown(SDL_Keycode key) const { return this->m_pushed_keys.find(key) != this->m_pushed_keys.end() ; }

bool Input::Keyboard::keyReleased(SDL_Keycode key) const { return m_last_released_key == key; }