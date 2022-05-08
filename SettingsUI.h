#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class SettingsUI: public sf::Drawable
{
public:
  SettingsUI(const sf::Vector2i& windowSize, uint32_t& numMelodyNotes);
  virtual void handleMousePress(const sf::Vector2i& mousePos);
public:
  sf::Text m_numMelodyNotesText;
  Button m_increaseMelodyNotes;
  Button m_decreaseMelodyNotes;
private:
  uint32_t& m_numMelodyNotes;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
