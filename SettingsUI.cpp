#include "SettingsUI.h"

SettingsUI::SettingsUI(AppInfo::Info& info):
  m_info(info)
{
  using namespace AppInfo;
  auto buttonSize = sf::Vector2f(WINDOW_WIDTH / 16.f, WINDOW_WIDTH / 16.f);
  m_increaseMelodyNotes.setSize({buttonSize.x, buttonSize.y});
  m_increaseMelodyNotes.setPosition({
    WINDOW_WIDTH - buttonSize.x * 1.2f,
    buttonSize.y * 0.2f});
  m_increaseMelodyNotes.setText("+");

  m_decreaseMelodyNotes.setSize({buttonSize.x, buttonSize.y});
  m_decreaseMelodyNotes.setPosition({
    WINDOW_WIDTH - buttonSize.x * 1.2f,
    buttonSize.y * 1.4f});
  m_decreaseMelodyNotes.setText("-");

  m_numMelodyNotesText.setFont(Font::get());
  m_numMelodyNotesText.setFillColor(sf::Color::White);
  m_numMelodyNotesText.setPosition({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 10.f});
  m_numMelodyNotesText.setString("# of Melody Notes: " + std::to_string(m_info.numMelodyNotes));
}

void SettingsUI::handleMousePress(const sf::Vector2i& mousePos)
{
  if (m_increaseMelodyNotes.inButton(mousePos))
  {
    if (m_info.numMelodyNotes < 200)
    {
      m_info.numMelodyNotes++;
    }
  }
  if (m_decreaseMelodyNotes.inButton(mousePos))
  {
    if (m_info.numMelodyNotes > 1)
    {
      m_info.numMelodyNotes--;
    }
  }
  m_numMelodyNotesText.setString("# of Melody Notes: " + std::to_string(m_info.numMelodyNotes));
}

void SettingsUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_increaseMelodyNotes, states);
  target.draw(m_decreaseMelodyNotes, states);
  target.draw(m_numMelodyNotesText, states);
}