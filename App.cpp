#include "App.h"

static const uint32_t WINDOW_HEIGHT = 720;
static const uint32_t WINDOW_WIDTH = 1280;
static const uint32_t BUTTON_HEIGHT = WINDOW_HEIGHT / 6;
static const uint32_t BUTTON_WIDTH = WINDOW_WIDTH / 3;

bool isInside(const sf::Vector2i& mousePos, const Button& button)
{
  const sf::Vector2f& buttonPos = button.getPosition();
  const sf::Vector2f& buttonSize = button.getSize();
  if (mousePos.x >= buttonPos.x && mousePos.y >= buttonPos.y &&
    mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y <= buttonPos.y + buttonSize.y)
  {
    return true;
  }
  return false;
}

void App::handleButtonClicks(const sf::Vector2i& mousePos)
{
  if (isInside(mousePos, m_playButton))
  {
    m_musicBuffer = AudioGenerator::generateMusic(m_soundBuffers);
    m_music.setBuffer(m_musicBuffer);
    m_music.play();
  }
  if (isInside(mousePos, m_saveButton))
  {
    if (m_musicBuffer.getSampleCount() != 0)
    {
      for (int16_t i = 0; i < INT16_MAX; i++)
      {
        if (!std::filesystem::exists("song" + std::to_string(i) + ".wav"))
        {
          std::cout << "Saved as: song" + std::to_string(i) + ".wav\n";
          m_musicBuffer.saveToFile("song" + std::to_string(i) + ".wav");
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
    }
    if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        this->close();
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
  this->draw(m_playButton);
  this->draw(m_saveButton);
  this->display();
}

void App::update()
{
}

void App::start()
{
  this->create({WINDOW_WIDTH, WINDOW_HEIGHT}, "Music Generator v0.0", sf::Style::Close | sf::Style::Titlebar);
  this->setVerticalSyncEnabled(true);

  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::A / 2, 0.8f}, AudioGenerator::sine));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::C / 2, 0.8f}, AudioGenerator::sine));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::E / 2, 0.2f}, AudioGenerator::square));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::A / 2, 0.2f}, AudioGenerator::square));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::D / 2, 0.2f}, AudioGenerator::square));

  m_playButton.setSize({BUTTON_WIDTH, BUTTON_HEIGHT});
  m_playButton.setPosition({WINDOW_WIDTH / 2 - m_playButton.getSize().x / 2, WINDOW_HEIGHT / 2 - BUTTON_HEIGHT * 1.2});
  m_playButton.setText("Play Great Music");

  m_saveButton.setSize({BUTTON_WIDTH, BUTTON_HEIGHT});
  m_saveButton.setPosition({WINDOW_WIDTH / 2 - m_playButton.getSize().x / 2, WINDOW_HEIGHT / 2});
  m_saveButton.setText("Save Music");

  while (this->isOpen())
  {
    this->handleEvents();
    this->update();
    this->render();
  }
}