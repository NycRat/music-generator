#include "App.h"

App::App()
{
  this->create({1280, 720}, "Music Generator v0.0", sf::Style::Close | sf::Style::Titlebar);
  this->setFramerateLimit(240);
}

void App::start()
{
  sf::Event event;
  while (this->isOpen())
  {
    while (this->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        this->close();
      }
    }

    this->update();
    this->render();
  }
}

void App::render()
{
  this->clear();
  this->display();
}

void App::update()
{
}