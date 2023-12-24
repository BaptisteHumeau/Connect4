#ifndef GAMELOG_H
#define GAMELOG_H

#include <SFML\Graphics.hpp>

class GameLog
{
private:
    int _scoreComputer;
    int _scorePlayer;

    sf::Text _textBox;
    sf::Font _font;

public:
    GameLog(const std::string FONT_PATH, const int WINDOW_SIZE_Y);

    void updateScore(const int WINNER);
    void draw(sf::RenderWindow &window);
};

#endif
