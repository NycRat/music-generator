#include "App.h"

void App::handleButtonClicks(const sf::Vector2i& mousePos)
{
  m_settingsUI.handleMousePress(mousePos);
  m_audioUI.handleMousePress(mousePos);
  if (m_exitButton.inButton(mousePos))
  {
    this->close();
  }
}

void App::handleEvents()
{
  sf::Event event;
  while (this->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      this->close();
      return;
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
      this->handleButtonClicks(sf::Mouse::getPosition(*this));
    }
  }
}

void App::render()
{
  this->clear();
  this->draw(m_info.visualWaveform, m_info.waveformTransform);
  this->draw(m_audioUI);
  this->draw(m_exitButton);
  this->draw(m_settingsUI);
  this->display();
}

void App::update()
{
  if (m_info.visualWaveform.getVertexCount() &&
    m_info.music.getStatus() == sf::Sound::Playing)
  {
    float newOffset = (-m_info.music.getPlayingOffset().asSeconds() + 0.2f) * AudioSettings::AUDIO_SAMPLE_RATE;
    m_info.waveformTransform.translate(newOffset - m_curWaveformOffset, 0);
    m_curWaveformOffset = newOffset;
  }
}

void App::start()
{
  using namespace AppInfo;
  this->create({WINDOW_WIDTH, WINDOW_HEIGHT}, "Music Generator v0.2", sf::Style::Close | sf::Style::Titlebar);
  this->setVerticalSyncEnabled(true);

  std::vector<int16_t(*)(const AudioGenerator::AudioInfo&)> waveforms;
  waveforms.push_back(AudioGenerator::sine);
  waveforms.push_back(AudioGenerator::triangle);
  waveforms.push_back(AudioGenerator::square);
  waveforms.push_back(AudioGenerator::sawtooth);

  for (auto&& waveform : waveforms)
  {
    for (auto&& [noteName, frequency] : AudioGenerator::noteFrequencies)
    {
      m_info.possibleNotes.push_back({AudioGenerator::getSound({1, frequency,
        (waveform == AudioGenerator::sine) ? 0.6f : 0.2f}, waveform), noteName});
    }
  }

  m_exitButton.setSize({BUTTON_WIDTH / 2, BUTTON_HEIGHT});
  m_exitButton.setPosition({WINDOW_WIDTH - m_exitButton.getSize().x * 1.2f,
    WINDOW_HEIGHT - m_exitButton.getSize().y * 1.4f});
  m_exitButton.setText("Exit");

  while (this->isOpen())
  {
    this->handleEvents();
    this->update();
    this->render();
  }
}