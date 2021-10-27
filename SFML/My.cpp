//Filename: My.cpp
//Description: OOP Assignment 1 - Implementation file for my extra useful methods
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#include <string>
#include "My.h"

void ccmy::trimRight(std::string& str)
{
    std::string::size_type pos = str.find_last_not_of(" ");
    str.erase(pos + 1);
}

void ccmy::trimLeft(std::string& str)
{
    std::string::size_type pos = str.find_first_not_of(" ");
    str.erase(0, pos);
}

void ccmy::trim(std::string& str)
{
    trimRight(str);
    trimLeft(str);
}

int ccmy::roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = abs(numToRound) % multiple;
    if (remainder == 0)
        return numToRound;

    if (numToRound < 0)
        return -(abs(numToRound) - remainder);
    else
        return numToRound + multiple - remainder;
}