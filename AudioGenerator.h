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
  struct Note
  {
    sf::SoundBuffer sound;
    uint8_t key;
  };

  struct AudioInfo
  {
    uint64_t time;
    uint32_t hertz;
    float volume;
  };

  extern sf::SoundBuffer generateMusic(
    const std::vector<Note>& notes, const uint32_t& numMelodyNotes, const uint32_t& bpm);
  extern sf::SoundBuffer getSound(const AudioInfo&, int16_t(*func)(const AudioInfo&));
  extern int16_t square(const AudioInfo& info);
  extern int16_t sawtooth(const AudioInfo& info);
  extern int16_t random(const AudioInfo& info);
  extern int16_t sine(const AudioInfo& info);
  extern int16_t triangle(const AudioInfo& info);

  static std::unordered_map<uint8_t, uint32_t> noteFrequencies = {
    {'A', 440},
    {'B', 494},
    {'C', 523},
    {'D', 587},
    {'E', 629},
    {'F', 698},
    {'G', 784},
  };
};
