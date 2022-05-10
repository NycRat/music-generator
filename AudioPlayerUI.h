#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include "UI.h"
#include "Button.h"
#include "AudioGenerator.h"
#include "AppInfo.h"

class AudioPlayerUI: public UI
{
public:
  AudioPlayerUI(AppInfo::Info& info);
  virtual void handleMousePress(const sf::Vector2i& mousePos);
private:
  Button m_generateButton;
  Button m_playPauseButton;
  Button m_saveButton;
  AppInfo::Info& m_info;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
