#ifndef WINMESSAGE_H
#define WINMESSAGE_H

#include <SFML/Graphics.hpp>
#include <string>

class WinMessage
{
private:
    std::string _winner;
    sf::Text _textBoxMain;
    sf::Font _fontTitle;

    sf::Text _TextBoxBody;
    sf::Font _fontBody;

public:
    WinMessage(const sf::Color COLOR, const std::string FONT_TITLE, const std::string FONT_BODY, const int WINDOW_SIZE_X);
    void setWinner(const std::string WINNER, const int WINDOW_SIZE_X);

    void draw(sf::RenderWindow &window);
};

#endif
