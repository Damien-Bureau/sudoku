#include <iostream>
#include <fstream>
#include <chrono>
#include "matplotlibcpp.h"

#include "GameManager.h"
#include "BoardHelper.h"
#include "Utils.h"
#include "ANSI.h"

namespace plt = matplotlibcpp;

void showStats(int n, bool plot = false)
{
    GameManager gm;
    gm.setBoard(emptyBoard);
    std::cout << "Generating..." << std::endl;
    int nbIterations, totalIterations = 0;
    int minIterations = 10000;
    int maxIterations = 0;
    int meanIterations;
    std::vector<int> iterations;

    if (plot)
    {
        plt::ion();
        plt::figure_size(1000, 600);
        // plt::plot(iterations); // x = [0, 1, 2, ..., n-1], y = iterations[i]
        plt::title("Distribution du nombre d'itérations pour générer une grille pour " + std::to_string(n) + " itérations");
        plt::grid(true);
        plt::show();
    }

    for (int i = 1; i <= n; i++)
    {
        static auto startTime = std::chrono::steady_clock::now();
        nbIterations = gm.generateBoard();
        auto endTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (nbIterations < minIterations)
        {
            minIterations = nbIterations;
        }
        else if (nbIterations > maxIterations)
        {
            maxIterations = nbIterations;
        }
        totalIterations += nbIterations;
        iterations.push_back(nbIterations);

        if (i % 100 == 0)
        {
            meanIterations = totalIterations / i;

            // sleep(10);
            system("clear");
            std::cout << gm.displayBoard() << std::endl;
            std::cout << ANSI_BOLD ANSI_MAGENTA << i << " boards generated" ANSI_RESET << std::endl;
            std::cout << "Minimum iterations : " ANSI_GREEN ANSI_BOLD << minIterations << ANSI_RESET << std::endl;
            std::cout << "Maximum iterations : " ANSI_RED ANSI_BOLD << maxIterations << ANSI_RESET << std::endl;
            std::cout << "Mean iterations    : " << meanIterations << ANSI_RESET << std::endl;
            std::cout << "Elapsed time       : " << elapsed << " ms" << std::endl;
            std::cout << "Mean time per board: " << (float)((float)elapsed / (float)i) << " ms" << std::endl;
            std::cout << std::endl;
            // std::cin.ignore();

            if (plot)
            {
                plt::clf();
                plt::hist(iterations, 1000);
                plt::title("Distribution progressive (" + std::to_string(i) + " grilles)");
                plt::xlabel("Nb d'itérations");
                plt::ylabel("Fréquence");
                plt::xlim(0, 800);
                plt::ylim(0, 200);
                plt::pause(0.01);
            }
        }
        gm.setBoard(emptyBoard);
    }

    if (plot)
    {
        plt::show();
        std::cin.ignore();
    }
}

void writeBoardInFile()
{
    std::ofstream file;
    // file.open("board_full.csv");
    file.open("board_semi_empty.csv");

    GameManager gm;
    gm.generateBoard();
    std::cout << gm.displayBoard() << std::endl;
    // gm.removeDigitsFromBoard(30);
    std::cout << gm.displayBoard() << std::endl;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            file << gm.getFrame(x, y)->getDigit();
            if (x < BOARD_SIZE - 1)
                file << ' ';
        }
        file << '\n';
    }
    file.close();
    std::cout << "Board written in file." << std::endl;
}

/**
 * @param n n boards generated to build the dataset
 */
void buildDataset(int n)
{
    std::string datasetFolder = "dataset";
    std::string trainingFolder = datasetFolder + "/training";
    std::string testingFolder = datasetFolder + "/testing";

    int trainingSplit = 80;
    int testingSplit = 100 - trainingSplit;

    int i = 0;
    for (i = 0; i < (int)(trainingSplit / 100) * n; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (i = 0; i < (testingSplit / 100) * n; i++)
    {
    }
    std::cout << i << std::endl;
}

int main(int argc, char const *argv[])
{
    GameManager gm;
    system("clear");

    // std::cout << "\nPress ENTER to start" << std::endl;
    // std::cout << gm.displayBoard() << std::endl;
    // std::cin.ignore();

    // int nbIterations = gm.generateBoard();
    // std::cout << "\n"
    //           << gm.displayBoard() << std::endl;
    // std::cout << "Iterations: " << nbIterations << std::endl;

    // if (gm.isBoardValid())
    // {
    //     std::cout << "Valid board 👍\n"
    //               << std::endl;
    // }
    // else
    // {
    //     std::cout << "Error in board! ❌\n"
    //               << std::endl;
    // }

    showStats(10000, true);

    // gm.generateBoard();
    // std::cout << gm.displayBoard() << std::endl;
    // gm.removeDigitsFromBoard(50);
    // std::cout << gm.displayBoard() << std::endl;

    // writeBoardInFile();
    // buildDataset(10);

    return 0;
}
