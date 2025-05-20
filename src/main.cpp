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
    // std::cout << gm.displayBoard() << std::endl;

    return 0;
}
