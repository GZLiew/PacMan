#include <audio/manager.h>
#include <iostream>
Audio::Manager::Manager() {
  if (Mix_OpenAudio(FREQUENCY, FORMAT, SIZE, CHUNK_SIZE) != 0){
    Utils::showError("SDL_mixer failed to initialize: ");
    return;
	}
  const std::string prefix = "resources/sounds/";
  const std::vector<std::string> sounds = {
    "intro",
    "intermission",
    "death",
    "munch_a",
    "munch_b",
    "large_pellet",
    "ghost_eat",
    "siren",
    "vulnerable",
    "fruit",
    "extra_life",
    "booster"
  };
  const std::string postfix = ".wav";

  /*
  Mix_Chunk* c;
  c = Mix_LoadWAV("/resources/sounds/intro.wav");
  if(c == nullptr) {
    std::cout << "faiou" <<
  }
  */

  this->m_sounds = std::vector<std::unique_ptr<Mix_Chunk>>();
  for(int i = 0; i < SOUND_AMOUNT; i++) {
    this->m_sounds.push_back(std::unique_ptr<Mix_Chunk>(Mix_LoadWAV(std::string(prefix + sounds[i] + postfix).c_str())));
    if(this->m_sounds[i] == nullptr){
      Utils::showError("Failed to load sound: " + prefix + sounds[i] + postfix);
      return;
    }
    this->m_map[sounds[i]] = i;
  }
}

Audio::Manager::~Manager() {
  Mix_CloseAudio();
  Mix_Quit();
}

void Audio::Manager::setSound(const bool b) {
  this->m_soundOn = b;
}

void Audio::Manager::playSound(const std::string name) {
  if(!this->m_soundOn) return;

  int s = this->m_map[name];
  if (Mix_Playing(s))
		Mix_HaltChannel(s);

	Mix_PlayChannel(-1, this->m_sounds[s].get(), 0);
}