#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include "AudioGenerator.h"
#include "VisualAudio.h"

namespace AppInfo
{
  static const uint32_t WINDOW_HEIGHT = 720;
  static const uint32_t WINDOW_WIDTH = 1280;
  static const uint32_t BUTTON_HEIGHT = WINDOW_HEIGHT / 8;
  static const uint32_t BUTTON_WIDTH = WINDOW_WIDTH / 5;

  struct Info
  {
    std::vector<AudioGenerator::Note> possibleNotes;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;
    sf::VertexArray visualWaveform;
    sf::Transform waveformTransform;
    uint32_t numMelodyNotes = 3;
    uint32_t bpm = 60;
  };
}
