#include "Grid.h"
#include "WinMessage.h"

#include <SFML/Graphics.hpp>
#include <string>

const std::string GAME_TITLE = "Connect 4";
const int WINDOW_SIZE_X = 1600;
const int WINDOW_SIZE_Y = 900;
const int CELL_SIZE = 100;

int main()
{
    int cellColor = 1;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), GAME_TITLE);

    Grid grid(CELL_SIZE);

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)))
            {
                window.close();
                return 0;
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                int columnIndex = grid.checkCursorHover(event.mouseMove.x, event.mouseMove.y);

                switch (columnIndex)
                {
                case -1:
                    break;

                default:
                    grid.highlightColumn(columnIndex);
                    break;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                int columnIndex = grid.checkCursorHover(event.mouseButton.x, event.mouseButton.y);

                switch (columnIndex)
                {
                case -1:
                    break;

                default:
                    grid.fillColumn(columnIndex, cellColor);
                    switch (cellColor)
                    {
                    case 1:
                        cellColor = 2;
                        break;
                    case 2:
                        cellColor = 1;
                        break;
                    default:
                        break;
                    }

                    break;
                }
            }
        }

        if (grid.checkWin(1))
        {
            WinMessage winner("Yellow", sf::Color(255, 204, 0), "Data/FontFiles/RobotCrush.ttf", WINDOW_SIZE_X);
            winner.draw(window);
        }
        else if (grid.checkWin(2))
        {
            WinMessage winner("Red", sf::Color(255, 51, 0), "Data/FontFiles/RobotCrush.ttf", WINDOW_SIZE_X);
            winner.draw(window);
        }

        grid.draw(window);
        window.display();
    }

    return 0;
}
