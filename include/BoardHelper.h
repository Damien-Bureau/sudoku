#ifndef BOARD_HELPER_H
#define BOARD_HELPER_H

#include "Frame.h"
#include "GameManager.h"

Frame emptyBoard[BOARD_SIZE][BOARD_SIZE] = {
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) }
};

Frame simpleBoardExample[BOARD_SIZE][BOARD_SIZE] = {
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) },
    { Frame(1), Frame(2), Frame(3), Frame(4), Frame(5), Frame(6), Frame(7), Frame(8), Frame(9) }
};

Frame simpleBoardOneFrame[BOARD_SIZE][BOARD_SIZE] = {
    { Frame(1), Frame(2), Frame(3), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(4), Frame(5), Frame(6), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(7), Frame(8), Frame(9), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) },
    { Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0), Frame(0) }
};

#endif /* BOARD_HELPER_H */