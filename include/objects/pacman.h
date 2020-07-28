#pragma once

#include <entity.h>
#include <input/input.h>

namespace Objects {
    class Pacman {
        Pacman();
        void handleInput(Input::Input &keyboard);
        void update(float dt);

        void draw();
    };
}