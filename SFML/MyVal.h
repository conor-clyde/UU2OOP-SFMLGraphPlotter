//Filename: MyVal.cpp
//Description: OOP Assignment 1 - Header file for my validation methods
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#pragma once
#include <string>

namespace ccval
{
	bool ValidLength(std::string txt, int min, int max);
	bool ValidLetterNumberWhitespace(std::string txt);
	bool ValidLetterNumber(std::string txt);
	bool ValidNumber(std::string txt);
	char ValidYN(std::string msg);
	int ValidRangeInt(std::string msg, int min, int max);
}