#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "UI.h"
#include "Button.h"
#include "AudioGenerator.h"
#include "AppInfo.h"

class AudioPlayerUI: public UI
{
public:
  AudioPlayerUI(const sf::Vector2i& windowSize, AppInfo::Info& info);
  virtual void handleMousePress(const sf::Vector2i& mousePos);
private:
  Button m_playButton;
  AppInfo::Info& m_info;
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
