#pragma once

#include <SFML/Graphics.hpp>
#include "AppInfo.h"
#include "Button.h"

class SettingsUI: public sf::Drawable
{
public:
  SettingsUI(AppInfo::Info& info);
  virtual void handleMousePress(const sf::Vector2i& mousePos);
public:
  sf::Text m_numMelodyNotesText;
  Button m_increaseMelodyNotes;
  Button m_decreaseMelodyNotes;
private:
  AppInfo::Info& m_info;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
