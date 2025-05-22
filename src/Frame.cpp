#include <algorithm>
#include "Frame.h"

/* Constructors */

Frame::Frame()
    : digit(1), squareX(0), squareY(0), testedDigits(std::vector<int>())
{
}

Frame::Frame(int digit)
    : digit(digit), squareX(0), squareY(0), testedDigits(std::vector<int>())
{
}

Frame::Frame(int squareX, int squareY, int digit)
    : digit(digit), squareX(0), squareY(0), testedDigits(std::vector<int>())
{
}

/* Getters */

int Frame::getDigit()
{
    return this->digit;
}

std::string Frame::getDigitString()
{
    return std::to_string(this->digit);
}

int Frame::getSquareX()
{
    return this->squareX;
}

int Frame::getSquareY()
{
    return this->squareY;
}

std::vector<int> Frame::getTestedDigits()
{
    return this->testedDigits;
}

/* Setters */

void Frame::setDigit(int digit)
{
    this->digit = digit;
}

void Frame::setSquareCoordinates(int x, int y)
{
    this->squareX = x;
    this->squareY = y;
}

/* Methods */

void Frame::addTestedDigit(int digit)
{
    if (std::find(this->testedDigits.begin(), this->testedDigits.end(), digit) == this->testedDigits.end())
    {
        this->testedDigits.push_back(digit);
    }
}

void Frame::resetTestedDigits()
{
    this->testedDigits.clear();
}