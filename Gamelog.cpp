#include <SFML\Graphics.hpp>
#include <iostream>

#include "GameLog.h"
#include <string>

GameLog::GameLog(const std::string FONT_PATH, const int WINDOW_SIZE_Y)
{
    if (!this->_font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font.";
    }

    this->_scoreComputer = 0;
    this->_scorePlayer = 0;

    this->_textBox.setCharacterSize(20);
    this->_textBox.setFont(this->_font);
    this->_textBox.setFillColor(sf::Color::White);
    this->_textBox.setPosition(10, WINDOW_SIZE_Y - 70);
}

void GameLog::updateScore(const int WINNER)
{
    switch (WINNER)
    {
    case 1:
        this->_scorePlayer++;
        break;
    case 2:
        this->_scoreComputer++;
        break;

    default:
        break;
    }
}

void GameLog::draw(sf::RenderWindow &window)
{
    std::string toDisplay = "PLAYER SCORE: " + std::to_string(this->_scorePlayer) + "\nCOMPUTER SCORE: " + std::to_string(this->_scoreComputer);
    this->_textBox.setString(toDisplay);
    window.draw(this->_textBox);
}
