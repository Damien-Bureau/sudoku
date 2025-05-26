#include <algorithm>
#include <iostream>

#include "GameManager.h"
#include "Frame.h"
#include "Utils.h"
#include "ANSI.h"
#include "BoardHelper.h"

#define HORIZONTAL_SEPARATOR_SIMPLE "─"
#define HORIZONTAL_SEPARATOR_DOUBLE "═"
#define VERTICAL_SEPARATOR_SIMPLE "│"
#define VERTICAL_SEPARATOR_DOUBLE "║"

// #define DEBUG
// #define SHOW_BOARD_GENERATION

GameManager::GameManager()
{
    /* Set every digit to 0 */
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        std::fill_n(this->board[y], BOARD_SIZE, 0);
    }
    newRandomSeed();
}

std::string GameManager::displayBoard()
{
    std::string output = "\n";
    std::string temp_row = "";

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_row = "";
        if (y == 0)
        {
            temp_row += "┌─────────┬─────────┬─────────┐\n";
        }
        else if (y == 3 || y == 6 || y == 9)
        {
            temp_row += "├─────────┼─────────┼─────────┤\n";
        }
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (x == 0 || x == 3 || x == 6 || x == 9)
            {
                temp_row += VERTICAL_SEPARATOR_SIMPLE;
            }
            temp_row += " ";
            std::string digitString = this->board[y][x].getDigitString();
            if (digitString == "0")
            {
                temp_row += " ";
            }
            else
            {
                temp_row += digitString;
            }
            temp_row += " ";
        }
        output += temp_row + VERTICAL_SEPARATOR_SIMPLE "\n";
    }
    output += "└─────────┴─────────┴─────────┘\n";

    return output;
}

void GameManager::setBoard(Frame predefined_board[BOARD_SIZE][BOARD_SIZE])
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            this->board[y][x] = predefined_board[y][x];
        }
    }
}

int GameManager::generateBoard()
{
    this->setBoard(emptyBoard);
    int nbIterations = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            std::vector<int> availableDigits = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};

            /* Remove tested digits from available digits */
            std::vector<int> testedDigits = this->board[y][x].getTestedDigits();
            for (int &digit : testedDigits)
            {
                availableDigits.erase(std::find(availableDigits.begin(), availableDigits.end(), digit));
            }

            int digitToPlace;
            while ((int)availableDigits.size() > 0)
            {
                int randomIndex = getRandomNumber((int)availableDigits.size() - 1);
                digitToPlace = availableDigits[randomIndex];
#ifdef SHOW_BOARD_GENERATION
                system("clear");
#endif
#ifdef DEBUG
                std::cout << "Trying to place digit '" << digitToPlace << "' in frame (" << x << "," << y << ")" << std::endl;
                std::cout << "Available digits: ";
                for (const auto &digit : availableDigits)
                {
                    std::cout << digit << " ";
                }
                std::cout << std::endl;
                std::cout << "Tested digits: ";
                for (const auto &digit : testedDigits)
                {
                    std::cout << digit << " ";
                }
                std::cout << std::endl;
#endif
                nbIterations++;
                if (isPlacementPossible(x, y, digitToPlace))
                {
                    this->board[y][x].setDigit(digitToPlace);

#ifdef SHOW_BOARD_GENERATION
                    std::cout << "Iterations: " << nbIterations << std::endl;
                    std::cout << this->displayBoard() << std::endl;
                    // std::cin.ignore();
                    sleep(70);
#endif
                    break;
                }
                else
                {
                    availableDigits.erase(std::find(availableDigits.begin(), availableDigits.end(), digitToPlace));

#ifdef SHOW_BOARD_GENERATION
                    std::cout << "Iterations: " << nbIterations << std::endl;
                    std::cout << this->displayBoard() << std::endl;
                    // std::cin.ignore();
                    sleep(100);
#endif
                }
            }
            if ((int)availableDigits.size() == 0)
            {
                /* Reset current frame */
                this->board[y][x].setDigit(0);
                this->board[y][x].resetTestedDigits();

                /* Add tested digit to previous frame */
                std::pair<int, int> previousFrameCoordinates = this->getPreviousFrameCoordinates(x, y);
                int previousFrameX = previousFrameCoordinates.first;
                int previousFrameY = previousFrameCoordinates.second;
                this->board[previousFrameY][previousFrameX].addTestedDigit(this->board[previousFrameY][previousFrameX].getDigit());

                /* Reset previous frame */
#ifdef DEBUG
                std::cout << "Resetting previous frame (" << previousFrameX << "," << previousFrameY << ")" << std::endl;
#endif
                this->board[previousFrameY][previousFrameX].setDigit(0);

                /* Move to previous frame */
                x = this->getPreviousFrameCoordinates(previousFrameX, previousFrameY).first;
                y = this->getPreviousFrameCoordinates(previousFrameX, previousFrameY).second;

#ifdef DEBUG
                std::cout << "Moving to frame (" << x << "," << y << ")" << std::endl;
#endif
                // std::cin.ignore();
            }
        }
    }

    return nbIterations;
}

bool GameManager::isBoardValid()
{
    bool valid = true;
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    /*
     * Method:
     *   - get digits of column/row/square
     *   - sort digits
     *   - compare with expected
     */

    /* Check columns */
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        std::vector<int> columnDigits = this->getDigitsOfColumn(x);
        std::sort(columnDigits.begin(), columnDigits.end());
        if (columnDigits != expected)
        {
            valid = false;
            goto out;
        }
    }

    /* Check rows */
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        std::vector<int> rowDigits = this->getDigitsOfRow(y);
        std::sort(rowDigits.begin(), rowDigits.end());
        if (rowDigits != expected)
        {
            valid = false;
            goto out;
        }
    }

    /* Check squares */
    for (int squareY = 0; squareY < 3; squareY++)
    {
        for (int squareX = 0; squareX < 3; squareX++)
        {
            std::vector<int> squareDigits = this->getDigitsOfSquare(squareX * 3, squareY * 3);
            std::sort(squareDigits.begin(), squareDigits.end());
            if (squareDigits != expected)
            {
                valid = false;
                goto out;
            }
        }
    }

out:
    return valid;
}

void GameManager::removeDigitsFromBoard(int n)
{
    int randomX, randomY;
    for (int i = 0; i <= n; i++)
    {
        randomX = getRandomNumber(BOARD_SIZE - 1);
        randomY = getRandomNumber(BOARD_SIZE - 1);
        if (this->board[randomY][randomX].getDigit() == 0)
        {
            i--;
        }
        else
        {
            this->board[randomY][randomX].setDigit(0);
        }
    }
}

bool GameManager::isPlacementPossible(int x, int y, int digit)
{
    std::vector<int> columnDigits = this->getDigitsOfColumn(x);
    std::vector<int> rowDigits = this->getDigitsOfRow(y);
    std::vector<int> squareDigits = this->getDigitsOfSquare(x, y);

    /* Check column */
    for (int columnDigit : columnDigits)
    {
        if (columnDigit == digit)
        {
            return false;
        }
    }

    /* Check row */
    for (int rowDigit : rowDigits)
    {
        if (rowDigit == digit)
        {
            return false;
        }
    }

    /* Check square */
    for (int squareDigit : squareDigits)
    {
        if (squareDigit == digit)
        {
            return false;
        }
    }

    return true;
}

Frame *GameManager::getFrame(int x, int y)
{
    return &(this->board[y][x]);
}

std::vector<int> GameManager::getDigitsOfColumn(int x)
{
    std::vector<int> columnDigits;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        columnDigits.push_back(this->board[y][x].getDigit());
    }
    return columnDigits;
}

std::vector<int> GameManager::getDigitsOfRow(int y)
{
    std::vector<int> rowDigits;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        rowDigits.push_back(this->board[y][x].getDigit());
    }
    return rowDigits;
}

std::vector<int> GameManager::getDigitsOfSquare(int x, int y)
{
    std::vector<int> squareDigits;
    std::pair<int, int> squareCoord = this->getSquareCoordinates(x, y);
    std::vector<Frame *> squareFrames = this->getFramesOfSquare(squareCoord.first, squareCoord.second);
    for (Frame *frame : squareFrames)
    {
        squareDigits.push_back(frame->getDigit());
    }

    return squareDigits;
}

std::pair<int, int> GameManager::getSquareCoordinates(int x, int y)
{
    std::pair<int, int> coord;
    int squareX, squareY;

    if (x < 3)
    {
        squareX = 0;
    }
    else if (x < 6)
    {
        squareX = 1;
    }
    else
    {
        squareX = 2;
    }

    if (y < 3)
    {
        squareY = 0;
    }
    else if (y < 6)
    {
        squareY = 1;
    }
    else
    {
        squareY = 2;
    }

    coord.first = squareX;
    coord.second = squareY;
    return coord;
}

std::vector<Frame *> GameManager::getFramesOfSquare(int squareX, int squareY)
{
    std::vector<Frame *> frames;
    for (int y = 0; y < SQUARE_SIZE; y++)
    {
        for (int x = 0; x < SQUARE_SIZE; x++)
        {
            frames.push_back(&(this->board[y + squareY * SQUARE_SIZE][x + squareX * SQUARE_SIZE]));
        }
    }
    return frames;
}

std::pair<int, int> GameManager::getPreviousFrameCoordinates(int x, int y)
{
    int newX = x;
    int newY = y;
    if (x == 0)
    {
        if (y == 0)
        {
            newX = 0;
            newY = 0;
        }
        else
        {
            newX = BOARD_SIZE - 1;
            newY--;
        }
    }
    else
    {
        newX--;
    }

    return {newX, newY};
}

std::string GameManager::getDigitsOfColumn_string(int x)
{
    std::vector<int> temp = this->getDigitsOfColumn(x);
    std::string output = "";
    for (int i = 0; i < (int)temp.size(); i++)
    {
        output += std::to_string(temp[i]);
    }
    return output;
}