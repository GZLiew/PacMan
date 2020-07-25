#include <doctest/doctest.h>
#include <input/keyboard.h>
#include <stdlib.h>

#include <array>

using namespace Input;

std::array<SDL_Keycode, SDL_KEY_COUNT> random_keys;

void configure() {
  srand(time(NULL));
  std::fill(random_keys.begin(), random_keys.end(), rand() % SDL_KEY_COUNT);
}

TEST_SUITE("Input::Keyboard") {
  TEST_CASE("keyboard should initialize without keys pressed") {
    configure();
    Keyboard board = Keyboard();
    // Pick random key and check it is initialized with false
    CHECK(board.isKeyDown(random_keys[rand() % SDL_KEY_COUNT]) == false);
  }

  TEST_CASE("keyboard should register keys pressed and released correctly") {
    configure();

    SDL_Keycode key = random_keys[rand() % SDL_KEY_COUNT];

    SDL_Event e = SDL_Event();
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = key;
    Keyboard board = Keyboard();
    board.update(e);

    // Pick random key and check it is initialized with false
    CHECK(board.isKeyDown(key) == true);
    CHECK(board.keyReleased(key) == true);

    e.type = SDL_KEYUP;
    e.key.keysym.sym = key;
    board.update(e);

    CHECK(board.isKeyDown(key) == false);
  }
}
