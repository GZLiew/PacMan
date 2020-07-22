#pragma once

#include <memory>
#include <vector>
#include <config.h>

class Application {

  public:
    Application(const Config &config);
    void run_loop();
    Config get_config();

  private:
    const Config &m_config;

};  // class Application
