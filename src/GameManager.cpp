#include <algorithm>

#include "GameManager.h"
#include "Frame.h"
#include "Utils.h"

#define HORIZONTAL_SEPARATOR "─"
#define VERTICAL_SEPARATOR "│"

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
    std::string temp_row;

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        temp_row = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            temp_row += VERTICAL_SEPARATOR " ";
            temp_row += this->board[y][x].getDigitString();
            temp_row += " ";
        }
        output += temp_row + VERTICAL_SEPARATOR "\n";
    }

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
    for (int squareY = 0; squareY < 3; squareY++)
    {
        for (int squareX = 0; squareX < 3; squareX++)
        {
            /* Get frames of current square */
            std::vector<Frame *> frames = this->getFramesOfSquare(squareX, squareY);

            /* Place each digit */
            for (int digit = 1; digit <= 9; digit++)
            {
                /* Check frames that already contain a digit */
                for (Frame *frame : frames)
                {
                    if (frame->getDigit() != 0)
                    {
                        frames.erase(std::find(frames.begin(), frames.end(), frame));
                    }
                }

                /* Check forbidden frames for current digit */
                std::vector<Frame *> framesAvailable = frames;
                for (Frame *frame : framesAvailable)
                {
                    /* Ignore frame if the digit is forbidden on it */
                    std::vector<int> frameForbiddenDigits = frame->getForbiddenDigits();
                    if (std::find(frameForbiddenDigits.begin(), frameForbiddenDigits.end(), digit) != frameForbiddenDigits.end())
                    {
                        framesAvailable.erase(std::find(framesAvailable.begin(), framesAvailable.end(), frame));
                    }
                }
                int nbFramesAvailable = framesAvailable.size();
                int randomDigitPlacement = getRandomNumber(nbFramesAvailable - 1);
                framesAvailable[randomDigitPlacement]->setDigit(digit);

                /* Forbid digit on row and column */
                // this->addForbiddenDigitToColumn(column, digit);
                // this->addForbiddenDigitToRow(row, digit);
            }
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