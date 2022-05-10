#pragma once

#include <SFML/Graphics.hpp>

namespace Font
{
  static sf::Font& get()
  {
    static sf::Font* font = new sf::Font();
    if (font->getInfo().family == "")
    {
      font->loadFromFile("default_font.ttf");
    }
    return *font;
  }
}

class UI: public sf::Drawable
{
public:
  virtual void handleMousePress(const sf::Vector2i& mousePos) = 0;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
