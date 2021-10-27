//Filename: My.h
//Description: OOP Assignment 1 - Header file for my extra useful methods
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#pragma once

namespace ccmy
{
    void trimRight(std::string& strs);
    void trimLeft(std::string& str);
    void trim(std::string& str);
    int roundUp(int numToRound, int multiple);
}

