#include <objects/pacman.h>

Objects::Pacman::Pacman(std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({32.0f, 32.0f}, {15 * 16.f, 27.5 * 16.f}, {0.f, 0.f},
             Collision::Hitbox({16.0f, 16.0f}, {15 * 16.f - 8, 27.5 * 16.f - 8})),
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
  // Update animation
  this->m_animation_state += 1;
  if (this->m_animation_state == PACMAN_ANIMATION_STATES) this->m_animation_state = 0;

  /*
  double y = this->hitbox.pos.y;
  double x = this->hitbox.pos.x;

  switch (this->m_next_direction) {
    case UP:
      if (mtrx[((y - 1) / 16)][(x / 16)]) {
        this->velocity = {0.0, -1.0};
        this->m_direction = this->m_next_direction;
        this->m_next_direction = NONE;
      }
      break;
    case DOWN:
      if (mtrx[((y) / 16) + 1][((x) / 16)]) {
        this->velocity = {0.0, 1.0};
        this->m_direction = this->m_next_direction;
        this->m_next_direction = NONE;
      }
      break;
    case LEFT:
      if (mtrx[(y) / 16][((x - 1) / 16)]) {
        this->velocity = {-1.0, 0.0};
        this->m_direction = this->m_next_direction;
        this->m_next_direction = NONE;
      }
      break;
    case RIGHT:
      if (mtrx[((y) / 16)][(x / 16) + 1]) {
        this->velocity = {1.0, 0.0};
        this->m_direction = this->m_next_direction;
        this->m_next_direction = NONE;
      }
      break;
  }
  */

  switch (this->m_next_direction) {
    case UP:
      this->velocity = {0.0, -1.0};
      this->m_direction = this->m_next_direction;
      this->m_next_direction = NONE;
      break;
    case DOWN:
      this->velocity = {0.0, 1.0};
      this->m_direction = this->m_next_direction;
      this->m_next_direction = NONE;
      break;
    case LEFT:
      this->velocity = {-1.0, 0.0};
      this->m_direction = this->m_next_direction;
      this->m_next_direction = NONE;
      break;
    case RIGHT:
      this->velocity = {1.0, 0.0};
      this->m_direction = this->m_next_direction;
      this->m_next_direction = NONE;
      break;
  }

  // Update position
  this->position += this->velocity * dt;
  this->hitbox.pos += this->velocity * dt;
}

void Objects::Pacman::draw() {
  int state = this->m_animation_state % PACMAN_ANIMATION_STATES;
  SDL_Rect renderQuad{(int)(this->position.x - this->dimension.x),
                      (int)(this->position.y - this->dimension.y), (int)this->dimension.x,
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

  SDL_Rect renderQuad2{(int)(this->hitbox.pos.x - this->hitbox.dim.x),
                       (int)(this->hitbox.pos.y - this->hitbox.dim.y), (int)this->hitbox.dim.x,
                       (int)this->hitbox.dim.y};

  SDL_SetRenderDrawColor(this->m_renderer->renderer().get(), 220, 20, 60, 1);
  SDL_RenderDrawRect(this->m_renderer->renderer().get(), &renderQuad2);
}