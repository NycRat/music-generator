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

static const uint32_t WINDOW_HEIGHT = 720;
static const uint32_t WINDOW_WIDTH = 1280;
static const uint32_t BUTTON_HEIGHT = WINDOW_HEIGHT / 8;
static const uint32_t BUTTON_WIDTH = WINDOW_WIDTH / 5;

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
  SettingsUI m_settingsUI{{WINDOW_WIDTH, WINDOW_HEIGHT}, m_info.numMelodyNotes};
  AudioPlayerUI m_audioUI{{WINDOW_WIDTH, WINDOW_HEIGHT}, m_info};
  Button m_saveButton;
  Button m_exitButton;
};
