#include <iostream>
#include "GameManager.h"
#include "BoardHelper.h"
#include "Utils.h"
#include "ANSI.h"

void showStats(int n)
{
    GameManager gm;
    gm.setBoard(emptyBoard);
    int nbIterations, totalIterations = 0;
    int minIterations = 10000;
    int maxIterations = 0;
    int meanIterations;
    for (int i = 1; i < n; i++)
    {
        nbIterations = gm.generateBoard();
        gm.setBoard(emptyBoard);
        if (nbIterations < minIterations)
        {
            minIterations = nbIterations;
        }
        else if (nbIterations > maxIterations)
        {
            maxIterations = nbIterations;
        }
        totalIterations += nbIterations;
        meanIterations = totalIterations / i;

        system("clear");
        std::cout << std::endl;
        std::cout << ANSI_BOLD ANSI_MAGENTA << i << " boards generated" ANSI_RESET << std::endl;
        std::cout << "Minimum iterations: " ANSI_GREEN ANSI_BOLD << minIterations << ANSI_RESET << std::endl;
        std::cout << "Maximum iterations: " ANSI_RED ANSI_BOLD << maxIterations << ANSI_RESET << std::endl;
        std::cout << "Mean iterations   : " << meanIterations << ANSI_RESET << std::endl;
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    GameManager gm;

    system("clear");
    // std::cout << "\nPress ENTER to start" << std::endl;
    // std::cout << gm.displayBoard() << std::endl;
    // std::cin.ignore();

    int nbIterations = gm.generateBoard();
    std::cout << "\n"
              << gm.displayBoard() << std::endl;
    std::cout << "Iterations: " << nbIterations << std::endl;

    if (gm.isBoardValid())
    {
        std::cout << "Valid board 👍\n"
                  << std::endl;
    }
    else
    {
        std::cout << "Error in board! ❌\n"
                  << std::endl;
    }

    // showStats(100);
    return 0;
}
