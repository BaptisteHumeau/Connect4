#ifndef Cell_H
#define Cell_H

#include <SFML\Graphics.hpp>

class Cell
{
private:
    int _sideLength;
    int _xPos;
    int _yPos;

    bool _containsRed;
    bool _containsYellow;

    bool _highlighted;

    sf::RectangleShape _rectangle;

    int _tokenRadius;
    sf::CircleShape _token;

public:
    Cell(const int &CELL_SIZE, const int X_POS, const int Y_POS);

    void setHighlighted(const bool VALUE);
    void draw(sf::RenderWindow &window);
    bool containsCursor(const int X, const int Y);
    void fillCell(const int COLOR);
    bool containsRed() const;
    bool containsYellow() const;
    bool containsColor(const int COLOR);
    bool isFilled();
};

#endif