#include <objects/ghost.h>

Objects::Ghost::Ghost(GhostType t, std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({32.0f, 32.0f}, {13.5 * 16.f - 8, 26 * 16.f - 8}, {0.5f, 0.f},
             Collision::Hitbox({16.0f, 16.0f}, {13.5 * 16.f, 26 * 16.f})),
      m_type(t),
      m_renderer(renderer) {
  this->m_textures_down = this->m_textures_left = this->m_textures_right = this->m_textures_up
      = this->m_textures_none = std::vector<std::shared_ptr<SDL_Texture>>(GHOST_ANIMATION_STATES);

  std::string name = "";
  switch (this->m_type) {
    case BLINKY:
      name = "blinky";
      break;
    case PINKY:
      name = "pinky";
      break;
    case INKY:
      name = "inky";
      break;
    case CLYDE:
      name = "clyde";
      break;
  }

  for (int i = 0; i < GHOST_ANIMATION_STATES; i++)
    this->m_textures_none[i] = std::shared_ptr<SDL_Texture>(
        Utils::loadSDLTexture(
            renderer->renderer().get(),
            std::string("resources/" + name + "/" + std::to_string(i / 4 + 1) + ".bmp").c_str()),
        [](SDL_Texture *t) { SDL_DestroyTexture(t); });

  for (int i = 0; i < GHOST_ANIMATION_STATES; i++)
    this->m_textures_down[i] = std::shared_ptr<SDL_Texture>(
        Utils::loadSDLTexture(
            renderer->renderer().get(),
            std::string("resources/" + name + "/" + std::to_string(i / 4 + 1) + "_down.bmp")
                .c_str()),
        [](SDL_Texture *t) { SDL_DestroyTexture(t); });

  for (int i = 0; i < GHOST_ANIMATION_STATES; i++)
    this->m_textures_left[i] = std::shared_ptr<SDL_Texture>(
        Utils::loadSDLTexture(
            renderer->renderer().get(),
            std::string("resources/" + name + "/" + std::to_string(i / 4 + 1) + "_left.bmp")
                .c_str()),
        [](SDL_Texture *t) { SDL_DestroyTexture(t); });

  for (int i = 0; i < GHOST_ANIMATION_STATES; i++)
    this->m_textures_right[i] = std::shared_ptr<SDL_Texture>(
        Utils::loadSDLTexture(
            renderer->renderer().get(),
            std::string("resources/" + name + "/" + std::to_string(i / 4 + 1) + "_right.bmp")
                .c_str()),
        [](SDL_Texture *t) { SDL_DestroyTexture(t); });

  for (int i = 0; i < GHOST_ANIMATION_STATES; i++)
    this->m_textures_up[i] = std::shared_ptr<SDL_Texture>(
        Utils::loadSDLTexture(
            renderer->renderer().get(),
            std::string("resources/" + name + "/" + std::to_string(i / 4 + 1) + "_up.bmp").c_str()),
        [](SDL_Texture *t) { SDL_DestroyTexture(t); });

  /* initialize random seed: */
  srand(time(NULL));

  /* generate secret number between 1 and 10: */
  this->m_direction = static_cast<Direction>(rand() % 4);
}

void Objects::Ghost::update(float dt) {
  // Update animation
  this->m_animation_state += 1;
  if (this->m_animation_state == GHOST_ANIMATION_STATES) this->m_animation_state = 0;

  // Update position
  this->position = this->position + this->velocity * dt;
  this->hitbox.pos = this->hitbox.pos + this->velocity * dt;
}

void Objects::Ghost::checkDirection(std::vector<Direction> directions) {
  // Check if Pacman can go back
  bool gotDirection = false;
  while (!gotDirection) {
    auto direction = directions[rand() % directions.size()];
    switch (this->m_direction) {
      case UP:
        if (direction != DOWN) gotDirection = true;
        break;
      case DOWN:
        if (direction != UP) gotDirection = true;
        break;
      case LEFT:
        if (direction != RIGHT) gotDirection = true;
        break;
      case RIGHT:
        if (direction != LEFT) gotDirection = true;
        break;
      default:
        break;
    }
    if (gotDirection) {
      this->changeDirection(direction);
    }
  }
}

void Objects::Ghost::setScare(bool s) { this->m_is_scared = s; }

void Objects::Ghost::draw() {
  int state = this->m_animation_state % GHOST_ANIMATION_STATES;
  SDL_Rect renderQuad{(int)(this->position.x), (int)(this->position.y), (int)this->dimension.x,
                      (int)this->dimension.y};

  std::shared_ptr<SDL_Texture> texture = nullptr;
  switch (this->m_direction) {
    case UP:
      texture = this->m_textures_up[state];
      break;
    case DOWN:
      texture = this->m_textures_down[state];
      break;
    case LEFT:
      texture = this->m_textures_left[state];
      break;
    case RIGHT:
      texture = this->m_textures_right[state];
      break;
    default:
      texture = this->m_textures_none[state];
      break;
  }

  SDL_RenderCopyEx(this->m_renderer->renderer().get(), texture.get(), NULL, &renderQuad, 0, NULL,
                   SDL_FLIP_NONE);
}

void Objects::Ghost::changeDirection(Direction dir) {
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
  this->m_direction = dir;
}

void Objects::Ghost::updateVelocity(glm::vec2 vel) { this->velocity = vel; }