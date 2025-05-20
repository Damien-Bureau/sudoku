#include <algorithm>
#include <iostream>

#include "GameManager.h"
#include "Frame.h"
#include "Utils.h"
#include "ANSI.h"

#define HORIZONTAL_SEPARATOR_SIMPLE "─"
#define HORIZONTAL_SEPARATOR_DOUBLE "═"
#define VERTICAL_SEPARATOR_SIMPLE "│"
#define VERTICAL_SEPARATOR_DOUBLE "║"

GameManager::GameManager()
{
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

void GameManager::generateBoard()
{
    // for (int squareY = 0; squareY < 3; squareY++)
    for (int digit = 1; digit <= 9; digit++)
    {
        // for (int squareX = 0; squareX < 3; squareX++)
        for (int squareY = 0; squareY < 3; squareY++)
        {
            /* Place each digit */
            // for (int digit = 1; digit <= 9; digit++)
            for (int squareX = 0; squareX < 3; squareX++)
            {
                /* Get frames of current square */
                std::vector<Frame *> frames = this->getFramesOfSquare(squareX, squareY);
                std::vector<std::pair<int, int>> framesCoordinates = {{0, 0},
                                                                      {0, 1},
                                                                      {0, 2},
                                                                      {1, 0},
                                                                      {1, 1},
                                                                      {1, 2},
                                                                      {2, 0},
                                                                      {2, 1},
                                                                      {2, 2}};

                /* Remove frames that already contain a digit */
                int nbFrames = (int)frames.size();
                for (int i = 0; i < nbFrames; i++)
                {
                    Frame *frame = frames[i];
                    std::pair<int, int> frameCoordinates = framesCoordinates[i];
                    if (frame->getDigit() != 0)
                    {
                        frames.erase(std::find(frames.begin(), frames.end(), frame));
                        framesCoordinates.erase(std::find(framesCoordinates.begin(), framesCoordinates.end(), frameCoordinates));
                        nbFrames--;
                    }
                }

                /* Add available frames for current digit */
                std::vector<Frame *> availableFrames;
                std::vector<std::pair<int, int>> availableFramesCoordinates;
                for (int i = 0; i < nbFrames; i++)
                {
                    Frame *frame = frames[i];
                    std::pair<int, int> frameCoordinates = framesCoordinates[i];

                    /* Add frame if the digit is not forbidden on it */
                    std::vector<int> frameForbiddenDigits = frame->getForbiddenDigits();
                    if (std::find(frameForbiddenDigits.begin(), frameForbiddenDigits.end(), digit) == frameForbiddenDigits.end())
                    {
                        availableFrames.push_back(frame);
                        availableFramesCoordinates.push_back(frameCoordinates);
                    }
                }
                int nbAvailableFrames = availableFrames.size() - 1;
                int randomDigitPlacement;
                bool tryAgain = false;
                if (nbAvailableFrames >= 0)
                {
                    randomDigitPlacement = getRandomNumber(nbAvailableFrames);
                    availableFrames[randomDigitPlacement]->setDigit(digit);
                }
                else
                {
                    tryAgain = true;
                }
                if (!tryAgain)
                {
                    /* Forbid digit on row and column */
                    int column = availableFramesCoordinates[randomDigitPlacement].second + squareX * SQUARE_SIZE;
                    int row = availableFramesCoordinates[randomDigitPlacement].first + squareY * SQUARE_SIZE;
                    this->addForbiddenDigitToColumn(column, digit);
                    this->addForbiddenDigitToRow(row, digit);
                    std::cout << "Square: (" << squareX << "," << squareY << ")" << std::endl;
                    std::cout << "Column: " << column << std::endl;
                    std::cout << "Row   : " << row << std::endl;
                    std::cout << std::endl;
                    // std::cin.ignore();
                }

                // Display frames in current square as a 3x3 grid
                std::cout << "Empty frames in current square:\n";
                for (int row = 0; row < 3; ++row)
                {
                    for (int col = 0; col < 3; ++col)
                    {
                        auto it = std::find(framesCoordinates.begin(), framesCoordinates.end(), std::make_pair(row, col));
                        if (it != framesCoordinates.end())
                        {
                            std::cout << "(" << row << "," << col << ")";
                        }
                        else
                        {
                            std::cout << " ─── ";
                        }
                        if (col != 2)
                            std::cout << "  ";
                    }
                    std::cout << "\n";
                }
                std::cout << std::endl;

                // Display available frames for digit inline
                std::cout << "Available frames for digit '" << digit << "': " << std::endl;
                for (const auto &coord : availableFramesCoordinates)
                {
                    std::cout << "(" << coord.first << "," << coord.second << ") ";
                }
                std::cout << std::endl;
                // std::cin.ignore();
                // sleep(100);
                if (tryAgain)
                {
                    std::cout << ANSI_RED "Unable to place digit '" << digit << "'!" ANSI_RESET << std::endl;
                    std::cin.ignore();
                }
                system("clear");
                std::cout << "Generating square (" << squareY << "," << squareX << ") ..." << std::endl;
                std::cout << "Press ENTER to place next digit" << std::endl;
                std::cout << this->displayBoard() << std::endl;
            }
            system("clear");
            // std::cout << ANSI_GREEN "\nSquare (" << squareY << "," << squareX << ") has been generated successfully" ANSI_RESET << std::endl;
            std::cout << this->displayBoard() << std::endl;
        }
    }
}

void GameManager::addForbiddenDigitToColumn(int x, int digit)
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        this->board[y][x].addForbiddenDigit(digit);
    }
}

void GameManager::addForbiddenDigitToRow(int y, int digit)
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        this->board[y][x].addForbiddenDigit(digit);
    }
}

std::vector<int> GameManager::getDigitsOfColumn(int x)
{
    std::vector<int> column_digits;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        column_digits.push_back(this->board[y][x].getDigit());
    }
    return column_digits;
}

std::vector<int> GameManager::getDigitsOfRow(int y)
{
    std::vector<int> row_digits;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        row_digits.push_back(this->board[y][x].getDigit());
    }
    return row_digits;
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

std::string GameManager::getDigitsOfColumn_string(int x)
{
    std::vector<int> temp = this->getDigitsOfColumn(0);
    std::string output = "";
    for (int i = 0; i < (int)temp.size(); i++)
    {
        output += std::to_string(temp[i]);
    }
    return output;
}