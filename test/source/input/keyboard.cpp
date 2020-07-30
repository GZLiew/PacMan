#include <doctest/doctest.h>
#include <input/keyboard.h>
#include <stdlib.h>

#include <array>

using namespace Input;

std::map<Action, SDL_Keycode> random_mapping;
std::array<SDL_Keycode, SDL_KEY_COUNT> random_keys;
std::array<Action, ACTION_COUNT> random_actions;

void configure_input_keyboard_test() {
  srand(time(NULL));
  std::fill(random_keys.begin(), random_keys.end(), rand() % SDL_KEY_COUNT);
  std::fill(random_actions.begin(), random_actions.end(),
            static_cast<Action>(rand() % ACTION_COUNT));
  random_mapping = std::map<Action, SDL_Keycode>();
  for (auto &i : random_actions) {
    random_mapping.insert(std::make_pair(i, random_keys[rand() % SDL_KEY_COUNT]));
  }
}

TEST_SUITE("Input::Keyboard") {
  TEST_CASE("keyboard should initialize without keys pressed") {
    configure_input_keyboard_test();
    Keyboard board = Keyboard(random_mapping);
    // Pick random key and check it is initialized with false
    CHECK(board.isKeyDown(random_actions[rand() % ACTION_COUNT]) == false);
  }

  TEST_CASE("keyboard should register keys pressed and released correctly") {
    configure_input_keyboard_test();

    SDL_Keycode key = random_keys[rand() % SDL_KEY_COUNT];
    Action act = random_actions[rand() % ACTION_COUNT];

    SDL_Event e = SDL_Event();
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = key;
    Keyboard board = Keyboard(random_mapping);
    board.update(e);

    // Pick random key and check it is initialized with false
    CHECK(board.isKeyDown(act) == true);
    CHECK(board.keyReleased(act) == true);

    e.type = SDL_KEYUP;
    e.key.keysym.sym = key;
    board.update(e);

    CHECK(board.isKeyDown(act) == false);
  }
}
