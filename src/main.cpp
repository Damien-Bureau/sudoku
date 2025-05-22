#include <iostream>
#include "GameManager.h"
#include "BoardHelper.h"

int main(int argc, char const *argv[])
{
    GameManager gm;

    system("clear");
    std::cout << "\nPress ENTER to start" << std::endl;
    std::cout << gm.displayBoard() << std::endl;
    std::cin.ignore();

    gm.generateBoard();
    std::cout << gm.displayBoard() << std::endl;

    if (gm.isBoardValid())
    {
        std::cout << "Valid board 👍\n" << std::endl;
    }
    else
    {
        std::cout << "Error in board! ❌\n" << std::endl;
    }

    return 0;
}
