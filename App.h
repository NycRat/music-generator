#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "AudioGenerator.h"
#include "Button.h"
#include "AppInfo.h"
#include "SettingsUI.h"
#include "AudioPlayerUI.h"
#include "VisualAudio.h"

class App: public sf::RenderWindow
{
public:
  void start();
private:
  void render();
  void update();
  void handleEvents();
  void handleButtonClicks(const sf::Vector2i& mousePos);
private:
  AppInfo::Info m_info;
  float m_curWaveformOffset = 0;

  SettingsUI m_settingsUI{m_info};
  AudioPlayerUI m_audioUI{m_info};
  Button m_exitButton;
};
