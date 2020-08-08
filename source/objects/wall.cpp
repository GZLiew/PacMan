#include <objects/wall.h>

Objects::Wall::Wall(Type t, const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({16.0f, 16.0f}, pos, {0.f, 0.f}, Collision::Hitbox({16.0f, 16.0f}, pos)),
      m_type(t),
      m_renderer(renderer) {
  // Set wall texture
  std::string path = "";
  switch (Utils::getTens(this->m_type)) {
    case CORNER_DOUBLE:
      path = "resources/level/corner_double.bmp";
      break;
    case CORNER_SHARP:
      path = "resources/level/corner_sharp.bmp";
      break;
    case CORNER_SINGLE:
      path = "resources/level/corner_single.bmp";
      break;
    case CORNER_SPECIAL:
      path = "resources/level/corner_special.bmp";
      break;
    case WALL_DOUBLE:
      path = "resources/level/wall_double.bmp";
      break;
    case WALL_SINGLE:
      path = "resources/level/wall_single.bmp";
      break;
    default:
      break;
  }

  // Set adequate orientation
  switch (this->m_type % 10) {
    case O_RIGHT:
      break;
    case O_DOWN:
      this->m_flip_type = SDL_FLIP_HORIZONTAL;
      break;
    case O_LEFT:
      this->m_degree = 90;
      this->m_flip_type = SDL_FLIP_HORIZONTAL;
      break;
    case O_UP:
      this->m_flip_type = SDL_FLIP_VERTICAL;
      break;

    case HORIZONTAL:
      this->m_degree = 90;
      break;
    case VERTICAL:
      break;
    case HORIZONTAL_UP:
      this->m_degree = 270;
      break;
    case HORIZONTAL_DOWN:
      this->m_degree = 90;
      this->m_flip_type = SDL_FLIP_VERTICAL;
      break;
    case VERTICAL_RIGHT:
      break;
    case VERTICAL_LEFT:
      this->m_flip_type = SDL_FLIP_HORIZONTAL;
      break;

    default:
      break;
  }

  this->m_texture = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(
      Utils::loadSDLTexture(renderer->renderer().get(), path.c_str()));
}

void Objects::Wall::draw() {
  SDL_Rect renderQuad{(int)this->hitbox.pos.x, (int)this->hitbox.pos.y, (int)this->hitbox.dim.x,
                      (int)this->hitbox.dim.y};
  SDL_RenderCopyEx(this->m_renderer->renderer().get(), this->m_texture.get(), NULL,
                    &renderQuad, this->m_degree, NULL, this->m_flip_type);
}