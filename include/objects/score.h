#pragma once

#include <entity.h>
#include <render/masterrenderer.h>

#include <memory>

namespace Objects {
  class Score : public Entity {
  public:
    Score(std::shared_ptr<Render::MasterRenderer> renderer);
    void add(int amount);
    void draw();

  private:
    int m_amount = 0;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
  };
}  // namespace Objects!pelet50->isEaten()