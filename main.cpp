#include "Grid.h"
#include "WinMessage.h"
#include "GameLog.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <cstdlib>

const std::string FONT_TITLE = "Data/FontFiles/RobotCrush.ttf";
const std::string FONT_BODY = "Data/FontFiles/RetroGaming.ttf";
const std::string GAME_TITLE = "Connect 4";
const int WINDOW_SIZE_X = 1600;
const int WINDOW_SIZE_Y = 900;
const int CELL_SIZE = 100;

int main()
{
    srand(time(0));
    rand();

    bool userTurn = true;
    bool gameOver = false;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), GAME_TITLE);
    WinMessage winner(sf::Color(255, 204, 0), FONT_TITLE, FONT_BODY, WINDOW_SIZE_X);
    GameLog gamelog(FONT_BODY, WINDOW_SIZE_Y);

    Grid grid(CELL_SIZE);

    while (window.isOpen())
    {
        window.clear();

        while (gameOver)
        {
            grid.draw(window);

            sf::Event gameOverEvent;
            while (window.pollEvent(gameOverEvent))
            {
                if (gameOverEvent.type == sf::Event::Closed ||
                    (gameOverEvent.type == sf::Event::KeyPressed && (gameOverEvent.key.code == sf::Keyboard::Escape || gameOverEvent.key.code == sf::Keyboard::Q)))
                {
                    window.close();
                    return 0;
                }
                else if (gameOverEvent.type == sf::Event::KeyPressed && gameOverEvent.key.code == sf::Keyboard::Enter)
                {
                    grid.reset();
                    gameOver = false;
                }
            }
        }

        userTurn = true;
        sf::Event inGameEvent;
        while (window.pollEvent(inGameEvent))
        {
            if (inGameEvent.type == sf::Event::Closed ||
                (inGameEvent.type == sf::Event::KeyPressed && (inGameEvent.key.code == sf::Keyboard::Escape || inGameEvent.key.code == sf::Keyboard::Q)))
            {
                window.close();
                return 0;
            }
            else if (inGameEvent.type == sf::Event::MouseMoved)
            {
                int columnIndex = grid.checkCursorHover(inGameEvent.mouseMove.x, inGameEvent.mouseMove.y);

                switch (columnIndex)
                {
                case -1:
                    break;

                default:
                    grid.highlightColumn(columnIndex);
                    break;
                }
            }
            else if (inGameEvent.type == sf::Event::MouseButtonPressed && inGameEvent.mouseButton.button == sf::Mouse::Left)
            {
                int columnIndex = grid.checkCursorHover(inGameEvent.mouseButton.x, inGameEvent.mouseButton.y);

                if (userTurn && !gameOver)
                {
                    switch (columnIndex)
                    {
                    case -1:
                        break;

                    default:
                        grid.fillColumn(columnIndex, 1);
                        grid.unhighlightAll();
                        grid.draw(window);
                        gamelog.draw(window);
                        window.display();
                        sf::sleep(sf::seconds(1));
                        userTurn = false;
                        break;
                    }
                }
            }
        }

        if (grid.checkWin(1))
        {
            winner.setWinner("Yellow", WINDOW_SIZE_X);
            gamelog.updateScore(1);
            winner.draw(window);
            gameOver = true;
        }

        if (!userTurn && !gameOver)
        {
            int computermove = grid.findMove();
            switch (computermove)
            {
            case -1:
                break;

            default:
                grid.fillColumn(computermove, 2);
                break;
            }
        }

        if (grid.checkWin(2))
        {
            winner.setWinner("Red", WINDOW_SIZE_X);
            gamelog.updateScore(2);
            winner.draw(window);
            gameOver = true;
        }

        gamelog.draw(window);
        grid.draw(window);
        window.display();
    }

    return 0;
}
