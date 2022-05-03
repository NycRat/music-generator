#include "App.h"

namespace App
{
  namespace
  {
    static sf::RenderWindow& getWindow()
    {
      static sf::RenderWindow we;
      return we;
    }
    static void handleEvents()
    {
      static sf::Event event;
      sf::RenderWindow& window = getWindow();
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Escape)
          {
            window.close();
          }
        }
      }
    }
    static void render()
    {
      getWindow().clear();
      getWindow().display();
    }

    static void update()
    {
    }

    static sf::Sound getSound()
    {
    }
  }

  void start()
  {
    sf::RenderWindow& window = getWindow();
    window.create({1280, 720}, "Music Generator v0.0", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(240);

    sf::SoundBuffer soundBuffer = AudioGenerator::get({2, 220, 1}, AudioGenerator::square);
    sf::Sound sound(soundBuffer);
    sound.setVolume(40);
    sound.play();

    while (window.isOpen())
    {
      handleEvents();
      update();
      render();
    }
  }
}