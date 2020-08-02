#include <objects/pacman.h>

Objects::Pacman::Pacman() : Entity({32.0f, 32.0f}, {0.f, 0.f}, {0.f, 0.f}) {
  this->m_sprites = std::vector<std::unique_ptr<SDL_Surface>>(3);
  this->m_sprites[0]
      = std::unique_ptr<SDL_Surface>(Utils::loadSDLSurface("resources/pacman_1.bmp"));
  this->m_sprites[1]
      = std::unique_ptr<SDL_Surface>(Utils::loadSDLSurface("resources/pacman_2.bmp"));
  this->m_sprites[2]
      = std::unique_ptr<SDL_Surface>(Utils::loadSDLSurface("resources/pacman_3.bmp"));
}

void Objects::Pacman::handleInput(std::shared_ptr<Input::Input> input) {
  if (input->isKeyDown(Input::Action::UP)) {
    this->m_next_direction = UP;
  } else if (input->isKeyDown(Input::Action::DOWN)) {
    this->m_next_direction = DOWN;
  } else if (input->isKeyDown(Input::Action::LEFT)) {
    this->m_next_direction = LEFT;
  } else if (input->isKeyDown(Input::Action::RIGHT)) {
    this->m_next_direction = RIGHT;
  }
}

void Objects::Pacman::update(float dt) {
  this->hitbox.update(this->hitbox.pos += this->velocity * dt);
}

void Objects::Pacman::draw(std::shared_ptr<SDL_Surface> base) {
  SDL_Rect prop;
  prop.x = this->hitbox.pos.x;
  prop.y = this->hitbox.pos.y;
  prop.w = this->hitbox.dim.x;
  prop.h = this->hitbox.dim.y;

  SDL_SetColorKey(this->m_sprites[this->m_animation_state].get(), SDL_TRUE,
                  SDL_MapRGB(this->m_sprites[this->m_animation_state].get()->format, 0, 0, 0));
  SDL_BlitScaled(this->m_sprites[this->m_animation_state].get(), NULL, base.get(), &prop);
}