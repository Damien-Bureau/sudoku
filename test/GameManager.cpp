#include <gtest/gtest.h>

#include "GameManager.h"
#include "Frame.h"
#include "BoardHelper.h"
#include "TestUtils.h"

#define GENERATE_EXPECTED

TEST(displayBoard, SimpleExample)
{
    const char *filename = "displayBoard_simpleExample.txt";

    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Generate expected board */
#ifdef GENERATE_EXPECTED
    writeInFile(filename, gm.displayBoard());
#endif

    /* Test */
    const std::string board = gm.displayBoard();
    const std::string expected_board = readFile(filename);
    EXPECT_STREQ(board.c_str(), expected_board.c_str());
}

TEST(getDigitsOfColumn, firstColumn)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 1, 1, 1, 1, 1, 1, 1, 1};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(0);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfColumn, middleColumn)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){6, 6, 6, 6, 6, 6, 6, 6, 6};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(5);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfColumn, lastColumn)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){9, 9, 9, 9, 9, 9, 9, 9, 9};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(BOARD_SIZE - 1);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfRow, firstRow)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(0);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfRow, middleRow)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(5);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfRow, lastRow)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(BOARD_SIZE - 1);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfSquare, topLeftSquare)
{
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardOneFrame);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfSquare(0, 0);
    EXPECT_EQ(result, expected_result);
}

TEST(getSquareCoordinates, oneTestPerSquare)
{
    /* Create GameManager */
    GameManager gm;

    /* Tests */
    std::pair<int, int> coord;
    // Top-left square (0,0)
    coord = gm.getSquareCoordinates(0, 0);
    EXPECT_EQ(coord.first, 0);
    EXPECT_EQ(coord.second, 0);

    // Top-middle square (3,0)
    coord = gm.getSquareCoordinates(3, 0);
    EXPECT_EQ(coord.first, 1);
    EXPECT_EQ(coord.second, 0);

    // Top-right square (6,0)
    coord = gm.getSquareCoordinates(6, 0);
    EXPECT_EQ(coord.first, 2);
    EXPECT_EQ(coord.second, 0);

    // Middle-left square (0,3)
    coord = gm.getSquareCoordinates(0, 3);
    EXPECT_EQ(coord.first, 0);
    EXPECT_EQ(coord.second, 1);

    // Center square (3,3)
    coord = gm.getSquareCoordinates(3, 3);
    EXPECT_EQ(coord.first, 1);
    EXPECT_EQ(coord.second, 1);

    // Middle-right square (6,3)
    coord = gm.getSquareCoordinates(6, 3);
    EXPECT_EQ(coord.first, 2);
    EXPECT_EQ(coord.second, 1);

    // Bottom-left square (0,6)
    coord = gm.getSquareCoordinates(0, 6);
    EXPECT_EQ(coord.first, 0);
    EXPECT_EQ(coord.second, 2);

    // Bottom-middle square (3,6)
    coord = gm.getSquareCoordinates(3, 6);
    EXPECT_EQ(coord.first, 1);
    EXPECT_EQ(coord.second, 2);

    // Bottom-right square (6,6)
    coord = gm.getSquareCoordinates(6, 6);
    EXPECT_EQ(coord.first, 2);
    EXPECT_EQ(coord.second, 2);
}

TEST(getPreviousFrameCoordinates, tests)
{
    /* Create GameManager */
    GameManager gm;

    /* Test */
    std::pair<int, int> coord = gm.getPreviousFrameCoordinates(0, 0);
    EXPECT_EQ(coord.first, 0);
    EXPECT_EQ(coord.second, 0);
    
    coord = gm.getPreviousFrameCoordinates(1, 0);
    EXPECT_EQ(coord.first, 0);
    EXPECT_EQ(coord.second, 0);

    coord = gm.getPreviousFrameCoordinates(0, 1);
    EXPECT_EQ(coord.first, 9);
    EXPECT_EQ(coord.second, 0);
    
    coord = gm.getPreviousFrameCoordinates(0, 3);
    EXPECT_EQ(coord.first, 9);
    EXPECT_EQ(coord.second, 2);
}

// TEST(getFramesOfSquare, simpleSquare)
// {
//     /* Create GameManager */
//     GameManager gm;
//     gm.setBoard(simpleBoardOneFrame);

//     /* Test */
//     std::vector<int> result;
//     std::vector<Frame *> frames = gm.getFramesOfSquare(0, 0);
//     for (Frame *frame : frames)
//     {
//         result.push_back(frame->getDigit());
//     }

//     const std::vector<int> expected_result = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     EXPECT_EQ(result, expected_result);
// }

// TEST(generateBoard, uniqueDigitsOnColumns)
// {
//     /* Create GameManager */
//     GameManager gm;
//     gm.generateBoard();

//     /* Test */
//     for (int x = 0; x < BOARD_SIZE; x++)
//     {
//         std::vector<int> columnDigits = gm.getDigitsOfColumn(x);
//         std::sort(columnDigits.begin(), columnDigits.end());
//         std::vector<int>::iterator it = std::adjacent_find(columnDigits.begin(), columnDigits.end());
//         EXPECT_EQ(it, columnDigits.end());
//     }
// }

// TEST(generateBoard, uniqueDigitsOnRows)>
// {
//     /* Create GameManager */
//     GameManager gm;
//     gm.generateBoard();

//     /* Test */
//     for (int y = 0; y < BOARD_SIZE; y++)
//     {
//         std::vector<int> rowDigits = gm.getDigitsOfRow(y);
//         std::sort(rowDigits.begin(), rowDigits.end());
//         std::vector<int>::iterator it = std::adjacent_find(rowDigits.begin(), rowDigits.end());
//         EXPECT_EQ(it, rowDigits.end());
//     }
// }