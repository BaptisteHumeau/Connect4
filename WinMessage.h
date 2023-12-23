#ifndef WINMESSAGE_H
#define WINMESSAGE_H

#include <SFML/Graphics.hpp>
#include <string>

class WinMessage
{
private:
    std::string _winner;
    sf::Text _textBox;
    sf::Font _font;

public:
    WinMessage(const std::string WINNER, const sf::Color COLOR, const std::string FONT_PATH, const int WINDOW_SIZE_X);

    void draw(sf::RenderWindow &window);
};

#endif
