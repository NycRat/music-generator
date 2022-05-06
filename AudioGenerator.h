#pragma once

#include <iostream>
#include <unordered_map>
#include <numbers>
#include <cmath>
#include <vector>
#include <SFML/Audio.hpp>

#include "Random.h"
#include "AudioSettings.h"

namespace AudioGenerator
{
  struct AudioInfo
  {
    uint64_t time;
    uint32_t hertz;
    float volume;
  };

  extern sf::SoundBuffer generateMusic(const std::vector<sf::SoundBuffer>& sounds);
  extern sf::SoundBuffer getSound(const AudioInfo&, int16_t(*func)(const AudioInfo&));
  extern int16_t square(const AudioInfo& info);
  extern int16_t sawtooth(const AudioInfo& info);
  extern int16_t random(const AudioInfo& info);
  extern int16_t sine(const AudioInfo& info);
  extern int16_t triangle(const AudioInfo& info);

  static std::unordered_map<int8_t, uint32_t> notes = {
    {'A', 440},
    {'B', 494},
    {'C', 523},
    {'D', 587},
    {'E', 629},
    {'F', 698},
    {'G', 784},
  };
};
