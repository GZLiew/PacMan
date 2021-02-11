#include <application.h>
#include <doctest/doctest.h>
#include <input/keyboard.h>
#include <state/cutscenestate.h>
#include <stdlib.h>

#include <array>

using namespace State;

TEST_SUITE("State::CutsceneState") {
  TEST_CASE("Should be built correctly") {
    Config config;
    Application app = Application(config);
    CutsceneState state = CutsceneState(app);
  }

  TEST_CASE("Should run all methods correctly") {
    Config config;
    Application app = Application(config);
    CutsceneState state = CutsceneState(app);

    SDL_Event e;
    state.handleEvent(e);
    state.handleInput();
    state.update(0);
    state.onOpen();
  }
}
