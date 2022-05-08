#include "App.h"

void App::handleButtonClicks(const sf::Vector2i& mousePos)
{
  m_settingsUI.handleMousePress(mousePos);
  m_audioUI.handleMousePress(mousePos);
  if (m_exitButton.inButton(mousePos))
  {
    this->close();
    return;
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
    if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        this->close();
        return;
      }
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
  this->draw(m_audioUI);
  this->draw(m_saveButton);
  this->draw(m_exitButton);
  this->draw(m_settingsUI);
  this->display();
}

void App::update()
{
}

void App::start()
{
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

  m_saveButton.setSize({BUTTON_WIDTH, BUTTON_HEIGHT});
  m_saveButton.setPosition({BUTTON_WIDTH * 0.1f,
    WINDOW_HEIGHT - BUTTON_HEIGHT - BUTTON_WIDTH * 0.1f});
  m_saveButton.setText("Save Music");

  m_exitButton.setSize({BUTTON_WIDTH / 3, BUTTON_HEIGHT / 2});
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