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
    int generateBoard();
    std::string displayBoard();
    bool isBoardValid();
    void removeDigitsFromBoard(int n);

    bool isPlacementPossible(int x, int y, int digit);

    Frame *getFrame(int x, int y);

    std::vector<int> getDigitsOfColumn(int x);
    std::vector<int> getDigitsOfRow(int y);
    std::vector<int> getDigitsOfSquare(int x, int y);
    /**
     * @param x The column index of the cell (0-based).
     * @param y The row index of the cell (0-based).
     * 
     * @return A std::pair<int, int> {squareX, squareY}
     */
    std::pair<int, int> getSquareCoordinates(int x, int y);
    std::vector<Frame *> getFramesOfSquare(int squareX, int squareY);

    std::pair<int, int> getPreviousFrameCoordinates(int x, int y);

    std::string getDigitsOfColumn_string(int x);
};

// #endif /* GAME_MANAGER_H */