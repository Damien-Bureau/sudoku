// #ifndef GAME_MANAGER_H
// #define GAME_MANAGER_H
#pragma once

#include <string>
#include "Frame.h"

#define BOARD_SIZE 9
#define SQUARE_SIZE 3

class GameManager
{
private:
    Frame board[BOARD_SIZE][BOARD_SIZE];

public:
    GameManager();
    void setBoard(Frame predefined_board[BOARD_SIZE][BOARD_SIZE]);
    void generateBoard();
    std::string displayBoard();

    void addForbiddenDigitToColumn(int x, int digit);
    void addForbiddenDigitToRow(int y, int digit);

    std::vector<int> getDigitsOfColumn(int x);
    std::vector<int> getDigitsOfRow(int y);
    std::vector<Frame *> getFramesOfSquare(int squareX, int squareY);

    std::string getDigitsOfColumn_string(int x);
};

// #endif /* GAME_MANAGER_H */