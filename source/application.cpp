#include <application.h>

Application::Application(const Config &config) : m_config(config){

}

void Application::run_loop() {

}

Config Application::get_config() {
  return this->m_config;
}
