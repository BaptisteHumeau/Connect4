#ifndef TOKEN_H
#define TOKEN_H

#include <SFML\Graphics.hpp>

class Token
{
private:
    int _radius;
    int _xPos;
    int _yPos;

    sf::CircleShape _circle;
    sf::Color _color;

public:
    Token(const std::string &COLOR);
};

#endif