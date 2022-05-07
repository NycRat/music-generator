#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "AudioGenerator.h"
#include "Button.h"

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
  std::vector<AudioGenerator::Note> m_possibleNotes;
  sf::SoundBuffer m_musicBuffer;
  sf::Sound m_music;
  Button m_playButton;
  Button m_saveButton;
  Button m_exitButton;
};
