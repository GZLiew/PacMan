#include <stdio.h>
#include <application.h>

int main(int argc, char* args[]) {
  Config config;
  Application app = Application(config);
  app.run_loop();
}