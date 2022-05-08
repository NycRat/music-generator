#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include "AudioGenerator.h"

namespace AppInfo
{
  struct Info
  {
    std::vector<AudioGenerator::Note> possibleNotes;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;
    uint32_t numMelodyNotes = 3;
  };
}
