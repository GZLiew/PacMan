#include <objects/level.h>
#include <iostream>

Objects::Level::Level(const glm::vec2& pos, std::shared_ptr<Render::MasterRenderer> renderer)
  : Entity({0.0f, 0.0f}, pos, {0.f, 0.f}) {
  this->m_walls = std::vector<std::shared_ptr<Wall>>();
  this->m_points10 = std::vector<std::shared_ptr<Points10>>();
  this->m_points50 = std::vector<std::shared_ptr<Points50>>();

  for(int i = 0; i < this->levelLayout.size(); i++) {
    for(int j = 0; j < this->levelLayout[i].size(); j++) {
      glm::vec2 tilePos = { j*16.0f, i*16.0f };
      tilePos += pos;
      switch(this->levelLayout[i][j]) {
        case 1:
          this->m_points10.push_back(std::shared_ptr<Points10>(new Points10(tilePos, renderer)));
          break;
        case 2:
          this->m_points50.push_back(std::shared_ptr<Points50>(new Points50(tilePos, renderer)));
          break;
        case 10 ... 69:
          Type type = (Type) this->levelLayout[i][j];
          this->m_walls.push_back(std::shared_ptr<Wall>(new Wall(type, tilePos, renderer)));
          break;
      }
    }
  }
}

void Objects::Level::draw() {
  for(auto wall = this->m_walls.begin(); wall != this->m_walls.end(); wall++)
    wall->get()->draw();
  for(auto point10 = this->m_points10.begin(); point10 != this->m_points10.end(); point10++)
    point10->get()->draw();
  for(auto point50 = this->m_points50.begin(); point50 != this->m_points50.end(); point50++)
    point50->get()->draw();
}