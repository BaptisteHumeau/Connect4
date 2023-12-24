#include "Grid.h"

#include <cstdlib>

Grid::Grid(const int CELL_SIZE) : _cellSize(CELL_SIZE)
{
    const int ORIGINAL_Y = 200;
    int startingPositionX = 500;
    int startingPositionY = ORIGINAL_Y;

    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            cells[j][i] = new Cell(CELL_SIZE, startingPositionX, startingPositionY);
            startingPositionY += CELL_SIZE;
        }

        startingPositionX += CELL_SIZE;
        startingPositionY = ORIGINAL_Y; // Reset Y position for the next column
    }
}

Grid::Grid(const Grid &other) : _cellSize(other._cellSize)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            // Create new cells and copy the contents
            cells[i][j] = new Cell(*(other.cells[i][j]));
        }
    }
}

Grid::~Grid()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            delete cells[i][j];
        }
    }
}

Grid &Grid::operator=(const Grid &other)
{
    if (this != &other)
    {
        _cellSize = other._cellSize;
        for (int i = 0; i < COLS; i++)
        {
            for (int j = 0; j < ROWS; j++)
            {
                *cells[j][i] = *other.cells[j][i];
            }
        }
    }

    // Return the modified object
    return *this;
}

int Grid::checkCursorHover(const int X, const int Y)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (this->cells[i][j]->containsCursor(X, Y))
            {
                return j;
            }
        }
    }

    return -1;
}

void Grid::highlightColumn(const int INDEX)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (j == INDEX)
            {
                this->cells[i][j]->setHighlighted(true);
            }
            else
            {
                this->cells[i][j]->setHighlighted(false);
            }
        }
    }
}

void Grid::unhighlightAll()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            this->cells[i][j]->setHighlighted(false);
        }
    }
}

void Grid::fillColumn(const int INDEX, const int COLOR)
{
    for (int i = 5; i >= 0; i--)
    {
        for (int j = 0; j < 7; j++)
        {
            if (j == INDEX && !(this->cells[i][j]->containsRed() || this->cells[i][j]->containsYellow()))
            {
                this->cells[i][j]->fillCell(COLOR);
                return;
            }
        }
    }
}

bool Grid::checkWin(const int COLOR) const
{
    // Check horizontally
    for (int i = 0; i < ROWS; i++)
    {
        int count = 0;
        for (int j = 0; j < COLS; j++)
        {
            if (this->cells[i][j]->containsColor(COLOR))
            {
                count++;
                if (count >= 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    // Check vertically
    for (int j = 0; j < COLS; j++)
    {
        int count = 0;
        for (int i = 0; i < ROWS; i++)
        {
            if (this->cells[i][j]->containsColor(COLOR))
            {
                count++;
                if (count >= 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    // Check diagonally (from top-left to bottom-right)
    for (int i = 0; i <= ROWS - 4; i++)
    {
        for (int j = 0; j <= COLS - 4; j++)
        {
            int count = 0;
            for (int k = 0; k < 4; k++)
            {
                if (this->cells[i + k][j + k]->containsColor(COLOR))
                {
                    count++;
                    if (count >= 4)
                    {
                        return true;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    // Check diagonally (from top-right to bottom-left)
    for (int i = 0; i <= ROWS - 4; i++)
    {
        for (int j = COLS - 1; j >= 3; j--)
        {
            int count = 0;
            for (int k = 0; k < 4; k++)
            {
                if (this->cells[i + k][j - k]->containsColor(COLOR))
                {
                    count++;
                    if (count >= 4)
                    {
                        return true;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    return false;
}

int Grid::findMove() const
{
    // Check for a move to block the opponent from winning
    for (int i = 0; i < COLS; i++)
    {
        // Simulate the opponent's move
        Grid simulatedGrid = *this;
        simulatedGrid.fillColumn(i, 2);

        // Check if the opponent has a winning move
        if (simulatedGrid.checkWin(2))
        {
            return i;
        }
    }

    // Check for a winning move
    for (int i = 0; i < COLS; i++)
    {
        Grid simulatedGrid = *this;
        simulatedGrid.fillColumn(i, 1);

        // Check if the move results in a win
        if (simulatedGrid.checkWin(1))
        {
            return i;
        }
    }

    // If no winning or blocking move, choose a random valid move
    int randomIndex = rand() % 7;
    return randomIndex;
}

void Grid::reset()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            this->cells[i][j]->reset();
        }
    }
}

void Grid::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            cells[j][i]->draw(window);
        }
    }
}
