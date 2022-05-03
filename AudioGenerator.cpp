#include "AudioGenerator.h"

namespace AudioGenerator
{
  sf::SoundBuffer get(const AudioInfo& info, int16_t(*func)(const AudioInfo&))
  {
    const int64_t& sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
    const size_t& seconds = info.time;

    int16_t* samples = new int16_t[sampleRate * seconds];
    for (size_t i = 0; i < sampleRate * seconds; i++)
    {
      samples[i] = func({i, info.hertz, info.volume});
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples, sampleRate * seconds, 1, sampleRate);

    delete[] samples;
    return buffer;
  }

  int16_t sawtooth(const AudioInfo& info)
  {
    int16_t ans = INT16_MIN * info.volume;
    ans += ((info.time * info.hertz) % (int16_t) (INT16_MAX * info.volume)) * 2;
    return ans;
  }

  int16_t square(const AudioInfo& info)
  {
    int freq = AudioSettings::AUDIO_SAMPLE_RATE / 440;
    return (info.time / freq) % 2 ? INT16_MAX : INT16_MIN;
  }

  int16_t sine(const AudioInfo& info)
  {
    int16_t volume = INT16_MAX * info.volume;
    int hertz = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    return volume * std::sin(info.time / (hertz / (2 * std::numbers::pi)));
  }

  int16_t random(const AudioInfo& info)
  {
    return Random::get();
  }
}