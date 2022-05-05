#include "AudioGenerator.h"

namespace AudioGenerator
{
  sf::SoundBuffer generateMusic(const std::vector<sf::SoundBuffer>& sounds)
  {
    sf::SoundBuffer musicBuffer;
    if (sounds.size() == 0)
    {
      return musicBuffer;
    }

    float bpm = (float) Random::get<int>(40, 120);
    uint32_t duration = 20; // seconds
    uint32_t sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
    int16_t* buffer = new int16_t[duration * sampleRate];
    sf::SoundBuffer soundBuffer;

    int drumIndex = 0;
    uint32_t drumDuration = (uint32_t) (sampleRate / (bpm / 60) / 4);
    const sf::SoundBuffer& drum = sounds[Random::get<size_t>(0, sounds.size() - 1)];

    std::vector<Note> melodyNotes;
    melodyNotes.push_back(Note::B);
    melodyNotes.push_back(Note::A);
    melodyNotes.push_back(Note::G);

    int melodyIndex = 0;
    uint32_t melodyDuration = (uint32_t) (sampleRate / (bpm / 60) / 4);
    const sf::SoundBuffer& melody = sounds[Random::get<size_t>(0, sounds.size() - 1)];

    for (uint64_t i = 0; i < (uint64_t) duration * sampleRate; i++)
    {
      int64_t soundValue = 0;
      // drum
      if (i / drumDuration % 2 == 0)
      {
        soundValue += drum.getSamples()[drumIndex];
        drumIndex++;
        drumIndex = drumIndex % drum.getSampleCount();
      }
      else
      {
        drumIndex = 0;
      }

      // melody
      soundValue += melody.getSamples()[melodyIndex];
      melodyIndex++;
      melodyIndex = melodyIndex % melody.getSampleCount();

      // ??
      if (soundValue > INT16_MAX)
      {
        soundValue = INT16_MAX;
      }
      else if (soundValue < INT16_MIN)
      {
        soundValue = INT16_MIN;
      }
      buffer[i] = (int16_t) soundValue;
    }

    musicBuffer.loadFromSamples(buffer, (uint64_t) duration * sampleRate, 1, sampleRate);
    delete[] buffer;

    return musicBuffer;
  }

  sf::SoundBuffer get(const AudioInfo& info, int16_t(*func)(const AudioInfo&))
  {
    const uint32_t& sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
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
    int16_t ans = (int16_t) (INT16_MIN * info.volume);
    ans += ((info.time * info.hertz) % (int16_t) (INT16_MAX * info.volume)) * 2;
    return ans;
  }

  int16_t square(const AudioInfo& info)
  {
    int dis = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    return (info.time / dis) % 2 ? INT16_MAX : INT16_MIN;
  }

  int16_t sine(const AudioInfo& info)
  {
    int16_t volume = (int16_t) (INT16_MAX * info.volume);
    int hertz = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    return (int16_t) (volume * std::sin(info.time / (hertz / (2 * std::numbers::pi))));
  }

  int16_t triangle(const AudioInfo& info)
  {
    int waveDis = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    uint64_t curDis = info.time % waveDis;

    bool neg = false;
    if (curDis > waveDis / 2)
    {
      neg = true;
      curDis -= waveDis / 2; // just make it normal then apply neg after
    }
    float height = info.volume * INT16_MAX;
    float width = waveDis / 4.f;
    float scale = height / width; // scale so that maxwidth * scale = maxheight

    int16_t ans;
    if (curDis > waveDis / 4) // subtract if going down
    {
      curDis -= waveDis / 4;
      ans = (int16_t) ((float) height - curDis * scale);
    }
    else
    {
      ans = (int16_t) (curDis * scale);
    }
    return ans * (neg ? -1 : 1);
  }

  int16_t random(const AudioInfo& info)
  {
    return (int16_t) (Random::get<int16_t>(INT16_MIN, INT16_MAX) * info.volume);
  }
}