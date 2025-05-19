#include <gtest/gtest.h>

#include "GameManager.h"
#include "Frame.h"
#include "BoardHelper.h"
#include "TestUtils.h"

// #define GENERATE_EXPECTED

TEST(displayBoard, SimpleExample) {
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

TEST(getDigitsOfColumn, firstColumn) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 1, 1, 1, 1, 1, 1, 1, 1};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(0);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfColumn, middleColumn) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){6, 6, 6, 6, 6, 6, 6, 6, 6};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(5);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfColumn, lastColumn) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){9, 9, 9, 9, 9, 9, 9, 9, 9};
    const std::vector<int> expected_result = gm.getDigitsOfColumn(BOARD_SIZE - 1);
    EXPECT_EQ(result, expected_result);
}


TEST(getDigitsOfRow, firstRow) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(0);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfRow, middleRow) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(5);
    EXPECT_EQ(result, expected_result);
}

TEST(getDigitsOfRow, lastRow) {
    /* Create GameManager */
    GameManager gm;
    gm.setBoard(simpleBoardExample);

    /* Test */
    const std::vector<int> result = (std::vector<int>){1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> expected_result = gm.getDigitsOfRow(BOARD_SIZE - 1);
    EXPECT_EQ(result, expected_result);
}
