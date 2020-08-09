#include <objects/pacman.h>

#include <iostream>

Objects::Pacman::Pacman(std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({32.0f, 32.0f}, {13.5 * 16.f - 8, 26 * 16.f - 8}, {0.f, 0.f},
             Collision::Hitbox({16.0f, 16.0f}, {13.5 * 16.f, 26 * 16.f})),
      m_renderer(renderer) {
  this->m_textures = std::vector<std::shared_ptr<SDL_Texture>>(PACMAN_ANIMATION_STATES);
  this->m_textures[0] = std::shared_ptr<SDL_Texture>(
      Utils::loadSDLTexture(renderer->renderer().get(), "resources/pacman/1.bmp"),
      [](SDL_Texture *t) { SDL_DestroyTexture(t); });
  this->m_textures[1] = this->m_textures[0];
  this->m_textures[2] = this->m_textures[0];
  this->m_textures[3] = this->m_textures[0];

  this->m_textures[4] = std::shared_ptr<SDL_Texture>(
      Utils::loadSDLTexture(renderer->renderer().get(), "resources/pacman/2.bmp"),
      [](SDL_Texture *t) { SDL_DestroyTexture(t); });
  this->m_textures[5] = this->m_textures[4];
  this->m_textures[6] = this->m_textures[4];
  this->m_textures[7] = this->m_textures[4];

  this->m_textures[8] = std::shared_ptr<SDL_Texture>(
      Utils::loadSDLTexture(renderer->renderer().get(), "resources/pacman/3.bmp"),
      [](SDL_Texture *t) { SDL_DestroyTexture(t); });
  this->m_textures[9] = this->m_textures[8];
  this->m_textures[10] = this->m_textures[8];
  this->m_textures[11] = this->m_textures[8];
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
  if (this->m_initially_stuck && this->m_direction == this->m_next_direction) {
    this->changeDirection(this->m_next_direction);
    this->m_initially_stuck = false;
  }
  // Check if Pacman can go back
  switch (this->m_next_direction) {
    case UP:
      if (this->m_direction == DOWN) this->changeDirection(UP);
      break;
    case DOWN:
      if (this->m_direction == UP) this->changeDirection(DOWN);
      break;
    case LEFT:
      if (this->m_direction == RIGHT) this->changeDirection(LEFT);
      break;
    case RIGHT:
      if (this->m_direction == LEFT) this->changeDirection(RIGHT);
      break;
    default:
      break;
  }
  // Update animation
  if (!this->m_stuck) this->m_animation_state += 1;
  if (this->m_animation_state == PACMAN_ANIMATION_STATES) this->m_animation_state = 0;

  // Update position
  this->position += this->velocity * dt;
  this->hitbox.pos += this->velocity * dt;
}

void Objects::Pacman::checkDirection(std::vector<Direction> directions) {
  // Check if next direction can be taken
  if (std::count(directions.begin(), directions.end(), this->m_next_direction)) {
    changeDirection(this->m_next_direction);
    // If not, check if current direction cant be taken and set pacman stuck
  } else if (!std::count(directions.begin(), directions.end(), this->m_direction)) {
    this->m_stuck = true;
    this->updateVelocity({0.0, 0.0});
  }
}

void Objects::Pacman::draw() {
  int state = this->m_animation_state % PACMAN_ANIMATION_STATES;
  SDL_Rect renderQuad{(int)(this->position.x), (int)(this->position.y), (int)this->dimension.x,
                      (int)this->dimension.y};

  switch (this->m_direction) {
    case UP:
      SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_textures[state].get(), NULL,
                       &renderQuad, 90, NULL, SDL_FLIP_HORIZONTAL);
      break;
    case DOWN:
      SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_textures[state].get(), NULL,
                       &renderQuad, 90, NULL, SDL_FLIP_NONE);
      break;
    case LEFT:
      SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_textures[state].get(), NULL,
                       &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
      break;
    case RIGHT:
      SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_textures[state].get(), NULL,
                       &renderQuad, 0, NULL, SDL_FLIP_NONE);
      break;
    default:
      SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_textures[state].get(), NULL,
                       &renderQuad, 0, NULL, SDL_FLIP_NONE);
      break;
  }

  SDL_Rect renderQuad2{(int)(this->hitbox.pos.x), (int)(this->hitbox.pos.y),
                       (int)this->hitbox.dim.x, (int)this->hitbox.dim.y};
}

void Objects::Pacman::changeDirection(Direction dir) {
  switch (dir) {
    case UP:
      this->updateVelocity({0.0, -1.0});
      break;
    case DOWN:
      this->updateVelocity({0.0, 1.0});
      break;
    case LEFT:
      this->updateVelocity({-1.0, 0.0});
      break;
    case RIGHT:
      this->updateVelocity({1.0, 0.0});
      break;
    default:
      break;
  }
  this->m_direction = this->m_next_direction;
  this->m_next_direction = NONE;
  this->m_stuck = false;
}

void Objects::Pacman::updateVelocity(glm::vec2 vel) { this->velocity = vel; }