//Filename: MyVal.cpp
//Description: OOP Assignment 1 - Implementation file for my validation methods
//Author: Conor Clyde
//Date: 26/10/21
//Last Updated: 27/10/21

#include <string>
#include <iostream>
#include "MyVal.h"
#include "My.h"

bool ccval::ValidLength(std::string txt, int min, int max)
{
    bool ok = true;
    if (txt.empty())
        ok = false;
    if (txt.length() < min || txt.length() > max)
        ok = false;

    return ok;
}

bool ccval::ValidLetterNumberWhitespace(std::string txt)
{
    bool ok = true;

    ccmy::trim(txt);

    if (txt.length() == 0)
        ok = false;
    else
    {
        for (int x = 0; x < txt.length(); x++)
        {
            if (!(isalnum(txt[x])) && !(isspace(txt[x])))
                ok = false;
        }
    }

    return ok;
}

bool ccval::ValidLetterNumber(std::string txt)
{
    bool ok = true;

    ccmy::trim(txt);

    if (txt.length() == 0)
        ok = false;
    else
    {
        for (int x = 0; x < txt.length(); x++)
        {
            if (!(isalnum(txt[x])))
                ok = false;
        }
    }

    return ok;
}


bool ccval::ValidNumber(std::string txt)
{
    bool ok = true;

    for (int x = 0; x < txt.length(); x++)
    {
        if (!(isdigit(txt[x])))
            ok = false;
    }

    return ok;
}

int ccval::ValidRangeInt(std::string msg, int min, int max)
{
    int num = 0;
    bool ok;

    do
    {
        try
        {
            ok = true;
            std::cout << msg << std::endl;

            std::cin >> num;
            if (!std::cin.good())
            {
                ok = false;

                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');

                throw "Invalid input.\n";
            }

            else if (num<min || num>max)
            {
                ok = false;

                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');

                throw num;
            }

        }
        catch (const char* ex)
        {
            std::cout << "Error: " << ex;
        }
        catch (...)
        {
            std::cout << "Error: Out of range. Please enter a value between " << min << " and " << max << std::endl;
        }

    } while (!ok);

    return num;
}

char ccval::ValidYN(std::string msg)
{
    char ch;

    do
    {
        std::cout << msg << std::endl;
        std::cin >> ch;

        ch = toupper(ch);

    } while (ch != 'Y' && ch != 'N');

    return ch;
}