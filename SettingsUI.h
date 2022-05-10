#pragma once

#include <SFML/Graphics.hpp>
#include "AppInfo.h"
#include "Button.h"

class SettingsUI: public sf::Drawable
{
public:
  SettingsUI(AppInfo::Info& info);
  virtual void handleMousePress(const sf::Vector2i& mousePos);
private:
  AppInfo::Info& m_info;

  sf::Text m_numMelodyNotesText;
  Button m_increaseMelodyNotes;
  Button m_decreaseMelodyNotes;

  sf::Text m_bpmText;
  Button m_increaseBpm;
  Button m_decreaseBpm;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
