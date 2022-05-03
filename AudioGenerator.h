#pragma once

#include <iostream>
#include <numbers>
#include <cmath>
#include <SFML/Audio.hpp>

#include "Random.h"
#include "AudioSettings.h"

namespace AudioGenerator
{
  struct AudioInfo
  {
    size_t time;
    int hertz;
    float volume;
  };

  extern sf::SoundBuffer get(const AudioInfo&, int16_t(*func)(const AudioInfo&));
  extern int16_t square(const AudioInfo& info);
  extern int16_t sawtooth(const AudioInfo& info);
  extern int16_t random(const AudioInfo& info);
  extern int16_t sine(const AudioInfo& info);
};
