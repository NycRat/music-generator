#pragma once

#include <SFML/Graphics.hpp>

class Button: public sf::Drawable
{
public:

  Button();
  void setPosition(const sf::Vector2f& position);
  void setText(const sf::String& text);
  void setSize(const sf::Vector2f& size);
  const sf::Vector2f& getSize() const;
  const sf::Vector2f& getPosition() const;
  bool inButton(const sf::Vector2i& mousePos) const;
private:
  sf::Text m_text;
  sf::RectangleShape m_rect;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
