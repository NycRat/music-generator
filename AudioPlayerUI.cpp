#include "AudioPlayerUI.h"

AudioPlayerUI::AudioPlayerUI(const sf::Vector2i& windowSize, AppInfo::Info& info)
  :m_info(info)
{
  uint32_t BUTTON_HEIGHT = windowSize.y / 8;
  uint32_t BUTTON_WIDTH = windowSize.x / 5;
  m_playButton.setSize({static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT)});
  m_playButton.setPosition({BUTTON_WIDTH * 0.1f,
    windowSize.y - BUTTON_HEIGHT * 2 - BUTTON_WIDTH * 0.2f});
  m_playButton.setText("Play Music");
}

void AudioPlayerUI::handleMousePress(const sf::Vector2i& mousePos)
{
  if (m_playButton.inButton(mousePos))
  {
    m_info.musicBuffer = AudioGenerator::generateMusic(m_info.possibleNotes, m_info.numMelodyNotes);
    m_info.music.setBuffer(m_info.musicBuffer);
    m_info.music.setLoop(true);
    m_info.music.play();
  }
}

void AudioPlayerUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_playButton, states);
}