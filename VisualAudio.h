#pragma once

#include <SFML/Graphics.hpp>
#include "AppInfo.h"

namespace VisualAudio
{
  sf::VertexArray getWaveform(const sf::SoundBuffer& musicBuffer);
}
