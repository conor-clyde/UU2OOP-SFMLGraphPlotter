#include <string>m
#include <iostream>
#include "common.h"
#include "Validation.h"

bool utilities::ValidLength(std::string txt, int min, int max) {
    bool ok = true;
    if (txt.empty())
        ok = false;
    if (txt.length() < min || txt.length() > max)
        ok = false;

    return ok;
}

bool utilities::ValidLetterNumberWhitespace(std::string txt) {
    bool ok = true;

    utilities::trim(txt);

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

std::string utilities::ValidLetterNumber(std::string msg) {
    std::string txt;
    bool ok = true;

    do {
        try {
            ok = true;
            std::cout << msg << std::endl;
            std::cin >> txt;

            std::cout << "[DEBUG] Input received: '" << txt << "'\n";


            utilities::trim(txt);



            if (txt.length() == 0) {
                ok = false;
                throw "Input cannot be empty.\n";
            } else {
                for (char ch : txt) {
                    if (!isalnum(static_cast<unsigned char>(ch))){
                        ok = false;
                        throw "Input must contain only letters and numbers.\n";
                    }
                }
            }
        }
        catch (const char* ex) {
            std::cout << "Error: " << ex;
        }
	} while (!ok);

    return txt;
}


bool utilities::ValidNumber(std::string txt) {
    bool ok = true;

    for (int x = 0; x < txt.length(); x++)
    {
        if (!(isdigit(txt[x])))
            ok = false;
    }

    return ok;
}

int utilities::ValidRangeInt(std::string msg, int min, int max) {
    int num = 0;
    bool ok;

    do {
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

char utilities::ValidYN(std::string msg) {
    char ch;

    do
    {
        std::cout << msg << std::endl;
        std::cin >> ch;

        ch = toupper(ch);

    } while (ch != 'Y' && ch != 'N');

    return ch;
}