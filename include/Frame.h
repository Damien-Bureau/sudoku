// #ifndef FRAME_H
// #define FRAME_H
#pragma once

#include <vector>
#include <string>

class Frame
{
private:
    int digit;
    int userDigit;
    bool showDigit = false;
    int squareX;
    int squareY;
    std::vector<int> testedDigits;

public:
    /* Constructors */
    Frame();
    Frame(int digit);
    Frame(int squareX, int squareY, int digit);

    /* Getters */
    int getDigit();
    std::string getDigitString();
    int getSquareX();
    int getSquareY();
    std::vector<int> getTestedDigits();

    /* Setters */
    void setDigit(int digit);
    void setSquareCoordinates(int squareX, int squareY);

    /* Methods */
    void addTestedDigit(int digit);
    void resetTestedDigits();
};

// #endif /* FRAME_H */