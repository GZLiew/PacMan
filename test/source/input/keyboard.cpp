#include <doctest/doctest.h>
#include <input/keyboard.h>
#include <stdlib.h>

using namespace Input;

TEST_CASE("keyboard should register events correctly") {
  // Initialize random seed
  srand(time(NULL));

  std::array<bool, SDL_KEY_COUNT> random_keys;
  Keyboard board = Keyboard();

  // Pick random key and check it is initialized with false
  CHECK(board.isKeyDown(random_keys[rand() % SDL_KEY_COUNT]) == false);
}