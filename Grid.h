#ifndef GRID_H
#define GRID_H

#include "Cell.h"

class Grid
{
private:
    static const int ROWS = 6;
    static const int COLS = 7;

    Cell *cells[ROWS][COLS];
    int _cellSize;

public:
    Grid(const int CELL_SIZE);
    ~Grid();

    int checkCursorHover(const int X, const int Y);
    void highlightColumn(const int COLUMN_INDEX);
    void fillColumn(const int COLUMN_INDEX, const int COLOR);
    bool checkWin(const int COLOR) const;
    int findMove() const;

    void draw(sf::RenderWindow &window);
};

#endif
