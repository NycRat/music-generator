#include "SettingsUI.h"

SettingsUI::SettingsUI(const sf::Vector2i& windowSize, uint32_t& numMelodyNotes):
  m_numMelodyNotes(numMelodyNotes)
{
  auto buttonSize = sf::Vector2f(windowSize.x / 16.f, windowSize.x / 16.f);
  m_increaseMelodyNotes.setSize({buttonSize.x, buttonSize.y});
  m_increaseMelodyNotes.setPosition({
    windowSize.x - buttonSize.x * 1.2f,
    buttonSize.y * 0.2f});
  m_increaseMelodyNotes.setText("+");

  m_decreaseMelodyNotes.setSize({buttonSize.x, buttonSize.y});
  m_decreaseMelodyNotes.setPosition({
    windowSize.x - buttonSize.x * 1.2f,
    buttonSize.y * 1.4f});
  m_decreaseMelodyNotes.setText("-");
}

void SettingsUI::handleMousePress(const sf::Vector2i& mousePos)
{
  if (m_increaseMelodyNotes.inButton(mousePos))
  {
    if (m_numMelodyNotes < 200)
    {
      m_numMelodyNotes++;
    }
  }
  if (m_decreaseMelodyNotes.inButton(mousePos))
  {
    if (m_numMelodyNotes > 0)
    {
      m_numMelodyNotes--;
    }
  }
}

void SettingsUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_increaseMelodyNotes, states);
  target.draw(m_decreaseMelodyNotes, states);
  target.draw(m_numMelodyNotesText, states);
}