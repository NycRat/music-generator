#pragma once

#include <SFML/Graphics.hpp>

class UI: public sf::Drawable
{
public:
  virtual void handleMousePress(const sf::Vector2i& mousePos) = 0;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
