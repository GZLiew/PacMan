#include <doctest/doctest.h>
#include <input.h>
#include <input/keyboard.h>
#include <objects/pacman.h>

#include <memory>

using namespace Objects;

TEST_SUITE("Object::Pacman") {
  TEST_CASE("Handles input without throwing") {
    auto input
        = std::shared_ptr<Input::Input>(new Input::Keyboard({{Input::Action::CONFIRM, SDLK_RETURN},
                                                             {Input::Action::DECLINE, SDLK_ESCAPE},
                                                             {Input::Action::UP, SDLK_UP},
                                                             {Input::Action::DOWN, SDLK_DOWN},
                                                             {Input::Action::LEFT, SDLK_LEFT},
                                                             {Input::Action::RIGHT, SDLK_RIGHT}}));

    Pacman pacman = Pacman();
    pacman.handleInput(input);
  }
}