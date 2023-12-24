#include "Cell.h"

#include <SFML\Graphics.hpp>

Cell::Cell(const int &CELL_SIZE, const int X_POS, const int Y_POS) : _highlighted(false)
{
    this->_sideLength = CELL_SIZE;
    this->_xPos = X_POS;
    this->_yPos = Y_POS;

    this->_containsRed = false;
    this->_containsYellow = false;
    this->_highlighted = false;

    this->_tokenRadius = (double)this->_sideLength / 4 * 3 / 2;

    this->_token = sf::CircleShape(_tokenRadius);
    this->_token.setOrigin(sf::Vector2f(_tokenRadius, _tokenRadius));
    this->_token.setPosition(sf::Vector2f(_xPos, _yPos));
    this->_token.setOutlineColor(sf::Color::White);
    this->_token.setOutlineThickness(2);

    this->_rectangle = sf::RectangleShape(sf::Vector2f(_sideLength, _sideLength));
    this->_rectangle.setOrigin(sf::Vector2f(_sideLength / 2, _sideLength / 2));
    this->_rectangle.setFillColor(sf::Color::Transparent);
    this->_rectangle.setPosition(sf::Vector2f(_xPos, _yPos));
    this->_rectangle.setOutlineColor(sf::Color::White);
    this->_rectangle.setOutlineThickness(1);
}

void Cell::setHighlighted(const bool VALUE)
{
    _highlighted = VALUE;
}

bool Cell::containsCursor(const int X, const int Y)
{
    if ((X > this->_xPos - _sideLength / 2 && X < this->_xPos + _sideLength / 2) &&
        (Y > this->_yPos - _sideLength / 2 && Y < this->_yPos + _sideLength / 2))
    {
        return true;
    }

    return false;
}

void Cell::fillCell(const int COLOR)
{
    if (!(this->_containsRed || this->_containsYellow))
    {
        switch (COLOR)
        {
        case 1:
            this->_containsYellow = true;
            break;
        case 2:
            this->_containsRed = true;
            break;
        default:
            break;
        }
    }
}

bool Cell::containsRed() const
{
    return this->_containsRed;
}

bool Cell::containsYellow() const
{
    return this->_containsYellow;
}

bool Cell::containsColor(const int COLOR)
{
    switch (COLOR)
    {
    case 1:
        return containsYellow();
        break;
    case 2:
        return containsRed();
        break;
    default:
        return false;
        break;
    }
}

bool Cell::isFilled()
{
    if (this->_containsRed || this->_containsYellow)
    {
        return true;
    }
    return false;
}

void Cell::draw(sf::RenderWindow &window)
{
    if (this->_highlighted)
    {
        this->_rectangle.setFillColor(sf::Color(255, 255, 255, 25));
    }
    else
    {
        this->_rectangle.setFillColor(sf::Color::Transparent);
    }

    if (this->_containsRed)
    {
        this->_token.setFillColor(sf::Color(255, 0, 0));
        window.draw(this->_token);
    }
    else if (this->_containsYellow)
    {
        this->_token.setFillColor(sf::Color(255, 204, 0));
        window.draw(this->_token);
    }

    window.draw(this->_rectangle);
}

void Cell::reset()
{
    this->_containsRed = false;
    this->_containsYellow = false;
    this->_highlighted = false;
}