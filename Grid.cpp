#include "Grid.h"

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

Grid::~Grid()
{
    // Deallocate memory for each Cell
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            delete cells[j][i];
        }
    }
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

    return -1; // Return -1 if no move is found
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
