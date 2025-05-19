#include <iostream>
#include "GameManager.h"
#include "BoardHelper.h"

int main(int argc, char const *argv[])
{
    GameManager gm;
    gm.generateBoard();
    std::cout << gm.displayBoard() << std::endl;

    return 0;
}
