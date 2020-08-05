#include <application.h>
#include <config.h>
#include <doctest/doctest.h>

TEST_SUITE("Application") {
  TEST_CASE("Application has default config") {
    Config config;
    Application app = Application(config);

    CHECK(app.getConfig().fullScreen == false);
    CHECK(app.getConfig().windowX == 800);
    CHECK(app.getConfig().windowY == 600);
  }
}