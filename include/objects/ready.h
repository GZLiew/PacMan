#pragma once

#include <entity.h>
#include <render/masterrenderer.h>

#include <memory>

namespace Objects {
  class Ready : public Entity {
  public:
    Ready(std::shared_ptr<Render::MasterRenderer> renderer);
    void add(int amount);
    void draw();

  private:
    int m_amount = 0;
    int m_highScore = 0;
    std::shared_ptr<Render::MasterRenderer> m_renderer;
  };
}  // namespace Objects