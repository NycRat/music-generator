#pragma once

#include <SFML/Graphics.hpp>

class App: public sf::RenderWindow
{
public:
  App();

  void start();
private:
  void render();
  void update();
};
