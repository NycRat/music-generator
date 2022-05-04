#include "App.h"

static const uint32_t WINDOW_HEIGHT = 720;
static const uint32_t WINDOW_WIDTH = 1280;

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
  this->display();
}

void App::update()
{
}

void App::start()
{
  this->create({WINDOW_WIDTH, WINDOW_HEIGHT}, "Music Generator v0.0", sf::Style::Close | sf::Style::Titlebar);
  this->setVerticalSyncEnabled(true);

  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::E, 0.4f}, AudioGenerator::random));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::A / 2, 0.4f}, AudioGenerator::square));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::G, 0.4f}, AudioGenerator::sawtooth));
  m_soundBuffers.push_back(AudioGenerator::get({2, AudioGenerator::C / 2, 0.8f}, AudioGenerator::sine));

  m_playButton.setSize({400, 150});
  m_playButton.setPosition({WINDOW_WIDTH / 2 - m_playButton.getSize().x / 2, WINDOW_HEIGHT / 2});
  m_playButton.setText("Play Great Music");

  while (this->isOpen())
  {
    this->handleEvents();
    this->update();
    this->render();
  }
}