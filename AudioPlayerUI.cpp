#include "AudioPlayerUI.h"

AudioPlayerUI::AudioPlayerUI(AppInfo::Info& info)
  :m_info(info)
{
  using namespace AppInfo;

  m_generateButton.setSize({static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT)});
  m_generateButton.setPosition({BUTTON_WIDTH * 0.1f, WINDOW_HEIGHT - BUTTON_HEIGHT * 3.6f});
  m_generateButton.setText("Generate Music");

  m_playPauseButton.setSize({static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT)});
  m_playPauseButton.setPosition({BUTTON_WIDTH * 0.1f, WINDOW_HEIGHT - BUTTON_HEIGHT * 2.4f});
  m_playPauseButton.setText("Play");

  m_saveButton.setSize({BUTTON_WIDTH, BUTTON_HEIGHT});
  m_saveButton.setPosition({BUTTON_WIDTH * 0.1f, WINDOW_HEIGHT - BUTTON_HEIGHT * 1.2f});
  m_saveButton.setText("Save Music");
}

void AudioPlayerUI::handleMousePress(const sf::Vector2i& mousePos)
{
  if (m_playPauseButton.inButton(mousePos))
  {
    if (m_info.music.getStatus() == sf::Sound::Playing)
    {
      m_info.music.pause();
      m_playPauseButton.setText("Play");
    }
    else
    {
      m_playPauseButton.setText("Pause");
      m_info.music.setLoop(true);
      m_info.music.play();
    }
  }
  if (m_generateButton.inButton(mousePos))
  {
    m_info.music.pause();
    m_info.musicBuffer = AudioGenerator::generateMusic(
      m_info.possibleNotes, m_info.numMelodyNotes, m_info.bpm);
    m_info.music.setBuffer(m_info.musicBuffer);
    m_info.visualWaveform = VisualAudio::getWaveform(m_info.musicBuffer);
    m_playPauseButton.setText("Play");
  }
  if (m_saveButton.inButton(mousePos))
  {
    if (m_info.musicBuffer.getSampleCount() != 0)
    {
      for (int16_t i = 0; i < INT16_MAX; i++)
      {
        if (!std::filesystem::exists("song" + std::to_string(i) + ".wav"))
        {
          std::cout << "Saved as: song" + std::to_string(i) + ".wav\n";
          m_info.musicBuffer.saveToFile("song" + std::to_string(i) + ".wav");
          break;
        }
        if (i == INT16_MAX - 1)
        {
          std::cout << "Cannot save song\n";
        }
      }
    }
  }
}

void AudioPlayerUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_playPauseButton, states);
  target.draw(m_generateButton, states);
  target.draw(m_saveButton, states);
}