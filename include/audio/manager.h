#pragma once

#include <SDL_mixer.h>
#include <deleters.h>
#include <utils.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#define FREQUENCY 44100
#define FORMAT MIX_DEFAULT_FORMAT
#define SIZE 2
#define CHUNK_SIZE 512
#define SOUND_AMOUNT 12

namespace Audio {
  class Manager {
  public:
    Manager();
    ~Manager();
    void setSound(const bool b);
    void stopSound(const std::string name);
    void playSound(const std::string name);

  private:
    bool m_soundOn = true;
    std::map<std::string, int> m_map;
    std::vector<std::unique_ptr<Mix_Chunk>> m_sounds;
  };
}  // namespace Audio