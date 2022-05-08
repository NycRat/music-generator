#include "Button.h"
#include <iostream>

namespace Font
{
  static sf::Font& get()
  {
    static sf::Font* font = new sf::Font();
    return *font;
  }
}

Button::Button()
{
  sf::Font& font = Font::get();
  if (font.getInfo().family == "")
  {
    font.loadFromFile("default_font.ttf");
  }
  m_text.setFont(font);
  m_text.setFillColor(sf::Color::Black);
}

bool Button::inButton(const sf::Vector2i& mousePos) const
{
  const sf::Vector2f& buttonPos = this->getPosition();
  const sf::Vector2f& buttonSize = this->getSize();
  if (mousePos.x >= buttonPos.x && mousePos.y >= buttonPos.y &&
    mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y <= buttonPos.y + buttonSize.y)
  {
    return true;
  }
  return false;
}

void Button::setPosition(const sf::Vector2f& position)
{
  m_rect.setPosition(position);
  m_text.setPosition({this->getPosition().x + this->getSize().x / 2 - m_text.getLocalBounds().width / 2,
    this->getPosition().y + this->getSize().y / 2 - m_text.getLocalBounds().height});
}

void Button::setText(const sf::String& text)
{
  m_text.setString(text);
  this->setPosition(this->getPosition());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_rect, states);
  target.draw(m_text, states);
}

void Button::setSize(const sf::Vector2f& size)
{
  m_rect.setSize(size);
}
const sf::Vector2f& Button::getSize() const
{
  return m_rect.getSize();
}
const sf::Vector2f& Button::getPosition() const
{
  return m_rect.getPosition();
}