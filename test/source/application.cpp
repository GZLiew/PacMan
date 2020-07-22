#include <doctest/doctest.h>
#include <application.h>
#include <config.h>

TEST_CASE("Application has default config") {
  Config config;
  Application app = Application(config);

  CHECK(app.get_config().fullScreen == false);
  CHECK(app.get_config().windowX == 800);
  CHECK(app.get_config().windowY == 600);
}