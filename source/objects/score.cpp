#include <objects/score.h>
#include <iostream>

Objects::Score::Score(std::shared_ptr<Render::MasterRenderer> renderer)
    : Entity({10*16, 16}, {9.5*16, .2*16}, {0.f, 0.f},
             Collision::Hitbox({0.0f, 0.0f}, {0.f,0.f})),
      m_renderer(renderer) {}

void Objects::Score::add(int amount) { this->m_amount += amount; }

void Objects::Score::draw() {
  SDL_Rect oneUpQuad{48, 4, 48, 16};
  this->m_renderer->drawText("1UP", 16, oneUpQuad);

  SDL_Rect hsQuad{152, 4, 160, 16};
  this->m_renderer->drawText("HIGH SCORE", 16, hsQuad);

  // Draw numeric scores
  std::string score = std::to_string(this->m_amount);
  int width = 9;
  int height = 9;
  for(int i = 0; i <= score.size(); i++){
    SDL_Rect scoreQuad{48 + i*width, 20, width, height};
    this->m_renderer->drawText(std::string(1, score[i]), 16, scoreQuad);
  }

  score = std::to_string(this->m_highScore);
  for(int i = 0; i <= score.size(); i++){
    SDL_Rect scoreQuad{152 + i*width, 20, width, height};
    this->m_renderer->drawText(std::string(1, score[i]), 16, scoreQuad);
  }

}