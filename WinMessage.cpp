#include "WinMessage.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

WinMessage::WinMessage(const sf::Color COLOR, const std::string FONT_TITLE, const std::string FONT_BODY, const int WINDOW_SIZE_X)
{
    if (!this->_fontTitle.loadFromFile(FONT_TITLE))
    {
        std::cerr << "Error loading font.";
    }

    if (!this->_fontBody.loadFromFile(FONT_BODY))
    {
        std::cerr << "Error loading font.";
    }

    this->_textBoxMain.setFont(this->_fontTitle);
    this->_textBoxMain.setFillColor(COLOR);
    this->_textBoxMain.setCharacterSize(70);

    this->_TextBoxBody.setFont(this->_fontBody);
    this->_TextBoxBody.setFillColor(sf::Color::White);
    this->_TextBoxBody.setCharacterSize(20);
    this->_TextBoxBody.setString("Press ENTER to try again");

    sf::FloatRect textRectBody = this->_TextBoxBody.getLocalBounds();
    this->_TextBoxBody.setOrigin(textRectBody.left + textRectBody.width / 2.0f, textRectBody.top + textRectBody.height / 2.0f);
    this->_TextBoxBody.setPosition(sf::Vector2f(WINDOW_SIZE_X / 2.0f, 800));
}

void WinMessage::setWinner(const std::string WINNER, const int WINDOW_SIZE_X)
{
    this->_winner = WINNER;
    std::string toDisplay = this->_winner + " Wins!";
    this->_textBoxMain.setString(toDisplay);

    sf::FloatRect textRectMain = _textBoxMain.getLocalBounds();
    _textBoxMain.setOrigin(textRectMain.left + textRectMain.width / 2.0f, textRectMain.top + textRectMain.height / 2.0f);
    _textBoxMain.setPosition(sf::Vector2f(WINDOW_SIZE_X / 2.0f, 70));
}

void WinMessage::draw(sf::RenderWindow &window)
{
    window.draw(this->_textBoxMain);
    window.draw(this->_TextBoxBody);
}
