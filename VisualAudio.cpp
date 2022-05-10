#include "VisualAudio.h"

namespace VisualAudio
{
  sf::VertexArray getWaveform(const sf::SoundBuffer& musicBuffer)
  {
    sf::VertexArray waveform;
    waveform.setPrimitiveType(sf::LineStrip);
    waveform.resize(musicBuffer.getSampleCount());

    float ratio = static_cast<float>(AppInfo::WINDOW_HEIGHT) / (static_cast<size_t>
      (INT16_MAX) * 2);

    for (size_t i = 0; i < musicBuffer.getSampleCount(); i += 1)
    {
      float y = (static_cast<int64_t>(musicBuffer.getSamples()[i]) + INT16_MAX) * ratio;
      float x = static_cast<float>(i);
      waveform.append(sf::Vertex({x, y}, sf::Color::Green));
    }
    return waveform;
  }
}