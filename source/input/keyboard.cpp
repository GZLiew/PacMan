#include <input/keyboard.h>

Input::Keyboard::Keyboard(std::map<Action, SDL_Keycode> mapping)
    : Input::Input(), m_key_mapping(mapping) {
  this->m_pushed_keys = std::set<SDL_Keycode>();
}

void Input::Keyboard::update(SDL_Event &e) {
  switch (e.type) {
    case SDL_KEYDOWN:
      this->m_last_released_key = this->findByKey(e.key.keysym.sym);
      this->m_pushed_keys.insert(e.key.keysym.sym);
      break;
    case SDL_KEYUP:
      this->m_pushed_keys.erase(e.key.keysym.sym);
      break;
    default:
      break;
  }
}

bool Input::Keyboard::isKeyDown(Action action) const {
  return this->m_pushed_keys.find(this->m_key_mapping.find(action)->second)
         != this->m_pushed_keys.end();
}

bool Input::Keyboard::keyReleased(Action action) const {
  return this->m_last_released_key == action;
}

Input::Action Input::Keyboard::findByKey(const SDL_Keycode &key) const {
  for (auto &i : this->m_key_mapping)
    if (i.second == key) return i.first;

  return Action::NONE;
}