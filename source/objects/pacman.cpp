#include <objects/pacman.h>

Objects::Pacman::Pacman() : Entity({32.0f, 32.0f}, {0.f, 0.f}, {0.f, 0.f}){}

void Objects::Pacman::handleInput(std::shared_ptr<Input::Input> input) {
    if(input->isKeyDown(Input::Action::UP)) {
        this->m_next_direction = UP;
    } else if(input->isKeyDown(Input::Action::DOWN)) {
        this->m_next_direction = DOWN;
    } else if(input->isKeyDown(Input::Action::LEFT)) {
        this->m_next_direction = LEFT;
    } else if(input->isKeyDown(Input::Action::RIGHT)) {
        this->m_next_direction = RIGHT;
    }
}

void Objects::Pacman::update(float dt){
    this->dt = dt;
}

void Objects::Pacman::draw() {
    
}