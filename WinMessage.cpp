#include "WinMessage.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

WinMessage::WinMessage(const std::string WINNER, const sf::Color COLOR, const std::string FONT_PATH, const int WINDOW_SIZE_X)
{
    if (!this->_font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font.";
    }

    this->_winner = WINNER;
    this->_textBox.setFont(this->_font); // Set the font for _textBox
    this->_textBox.setFillColor(COLOR);
    this->_textBox.setCharacterSize(70);

    std::string toDisplay = this->_winner + " Wins!";
    this->_textBox.setString(toDisplay);

    sf::FloatRect textRect = _textBox.getLocalBounds();
    _textBox.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    _textBox.setPosition(sf::Vector2f(WINDOW_SIZE_X / 2.0f, 70));
}

void WinMessage::draw(sf::RenderWindow &window)
{
    window.draw(this->_textBox);
}
