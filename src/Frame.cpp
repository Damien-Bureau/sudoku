#include "Frame.h"

/* Constructors */

Frame::Frame()
    : digit(1), squareX(0), squareY(0), forbidden_digits(std::vector<int>())
{
}

Frame::Frame(int digit)
    : digit(digit), squareX(0), squareY(0), forbidden_digits(std::vector<int>())
{
}

Frame::Frame(int squareX, int squareY, int digit)
    : digit(digit), squareX(0), squareY(0), forbidden_digits(std::vector<int>())
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

std::vector<int> Frame::getForbiddenDigits()
{
    return this->forbidden_digits;
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

void Frame::addForbiddenDigit(int digit)
{
    this->forbidden_digits.push_back(digit);
}