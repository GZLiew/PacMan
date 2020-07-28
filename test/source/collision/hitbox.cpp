#include <collision/hitbox.h>
#include <doctest/doctest.h>

using namespace Collision;

TEST_SUITE("Collision::Hitbox") {
  TEST_CASE("Should initialize correctly") {
    glm::vec2 v1 = glm::vec2{3.0f, 4.0f};

    Hitbox h1({1.0f, 2.0f}, v1);

    CHECK(h1.dim.x == 1.0f);
    CHECK(h1.dim.y == 2.0f);
    CHECK(h1.pos.x == 3.0f);
    CHECK(h1.pos.y == 4.0f);
  }

  TEST_CASE("Should detect collision correctly") {
    glm::vec2 pos1 = glm::vec2{0.0f, 0.0f};
    glm::vec2 pos2 = glm::vec2{0.0f, 0.0f};

    Hitbox h1({50.0f, 50.0f}, pos1);
    Hitbox h2({10.0f, 10.0f}, pos2);

    CHECK(h1.collide(h2) == true);

    glm::vec2 pos3 = glm::vec2{0.0f, 0.0f};
    glm::vec2 pos4 = glm::vec2{5.1f, 0.0f};

    Hitbox h3({5.0f, 5.0f}, pos3);
    Hitbox h4({5.0f, 5.0f}, pos4);

    CHECK(h3.collide(h4) == false);
  }
}
