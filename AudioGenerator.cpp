#include "AudioGenerator.h"

namespace AudioGenerator
{
  namespace
  {
    struct NoteInfo
    {
      const Note& note;
      const uint32_t& duration;
    };
    uint32_t getFourthNoteDuration(const Note& note, const float& bpm)
    {
      auto& sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
      uint32_t duration = sampleRate / noteFrequencies.at(note.key);
      duration = (static_cast<uint32_t>(round(sampleRate / (bpm / 60) / 4 / duration))) * duration;
      return duration;
    }
  };

  sf::SoundBuffer generateMusic(const std::vector<Note>& notes, const uint32_t& numMelodyNotes)
  {
    sf::SoundBuffer musicBuffer;
    if (notes.size() == 0)
    {
      return musicBuffer;
    }

    float bpm = static_cast<float>(Random::get<uint32_t>(40, 120));
    uint32_t duration = 20; // seconds
    const uint32_t& sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
    int16_t* buffer = new int16_t[duration * sampleRate];
    sf::SoundBuffer soundBuffer;

    int drumIndex = 0;

    const Note& drum = notes[Random::get<size_t>(0, notes.size() - 1)];
    uint32_t drumDuration = getFourthNoteDuration(drum, bpm);

    std::vector<NoteInfo> melodyNotes;
    for (uint32_t i = 0; i < numMelodyNotes; i++)
    {
      const Note& tempNote = notes[Random::get<size_t>(0, notes.size() - 1)];
      melodyNotes.push_back({tempNote, getFourthNoteDuration(tempNote, bpm)});
    }

    uint32_t melodyIndex = 0;
    uint32_t melodyNoteIndex = 0;

    for (uint64_t i = 0; i < static_cast<uint64_t>(duration) * sampleRate; i++)
    {
      int64_t soundValue = 0;
      // drum
      if (i / drumDuration % 2 == 0)
      {
        soundValue += drum.sound.getSamples()[drumIndex];
        drumIndex++;
        drumIndex = drumIndex % drum.sound.getSampleCount();
      }
      else
      {
        drumIndex = 0;
      }

      // melody
      // make sure to add to not do this if melody is stopped for a bit
      auto& curSound = melodyNotes[melodyNoteIndex].note.sound;
      soundValue += curSound.getSamples()[melodyIndex % curSound.getSampleCount()];
      melodyIndex++;
      if (melodyIndex > melodyNotes[melodyNoteIndex].duration)
      {
        melodyIndex = 0;
        melodyNoteIndex++;
        if (melodyNoteIndex >= melodyNotes.size())
        {
          melodyNoteIndex = 0;
        }
      }

      // stop integer overflow and underflow
      if (soundValue > INT16_MAX)
      {
        soundValue = INT16_MAX;
      }
      else if (soundValue < INT16_MIN)
      {
        soundValue = INT16_MIN;
      }
      buffer[i] = static_cast<int16_t>(soundValue);
    }

    musicBuffer.loadFromSamples(buffer, static_cast<uint64_t>(duration) * sampleRate, 1, sampleRate);
    delete[] buffer;

    return musicBuffer;
  }

  sf::SoundBuffer getSound(const AudioInfo& info, int16_t(*func)(const AudioInfo&))
  {
    const uint32_t& sampleRate = AudioSettings::AUDIO_SAMPLE_RATE;
    const auto totalSamples = (sampleRate / info.hertz) * info.time;

    int16_t* samples = new int16_t[totalSamples];

    for (size_t i = 0; i < totalSamples; i++)
    {
      samples[i] = func({i, info.hertz, info.volume});
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples, totalSamples, 1, sampleRate);

    delete[] samples;
    return buffer;
  }

  int16_t sawtooth(const AudioInfo& info)
  {
    int waveDis = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    uint64_t curDis = info.time % waveDis;

    float height = info.volume * INT16_MAX;
    float width = waveDis / 2.f;
    float scale = height / width; // scale so that maxwidth * scale = maxheight

    if (curDis > waveDis / 2) // subtract if going down
    {
      curDis -= waveDis / 2;
      return static_cast<int16_t>(curDis * scale - height);
    }
    else
    {
      return static_cast<int16_t>(curDis * scale);
    }
  }

  int16_t square(const AudioInfo& info)
  {
    int dis = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz / 2;
    return static_cast<int16_t>(((info.time % info.hertz) < dis ? INT16_MAX : INT16_MIN) * info.volume);
  }

  int16_t sine(const AudioInfo& info)
  {
    int16_t volume = static_cast<int16_t>(INT16_MAX * info.volume);
    int hertz = AudioSettings::AUDIO_SAMPLE_RATE / info.hertz;
    return static_cast<int16_t>(volume * std::sin(info.time / (hertz / (2 * std::numbers::pi))));
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
      ans = static_cast<int16_t>(height - curDis * scale);
    }
    else
    {
      ans = static_cast<int16_t>(curDis * scale);
    }
    return ans * (neg ? -1 : 1);
  }

  int16_t random(const AudioInfo& info)
  {
    return static_cast<int16_t>(Random::get<int16_t>(INT16_MIN, INT16_MAX) * info.volume);
  }
}