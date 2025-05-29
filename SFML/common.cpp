#include <string>
#include "common.h"

void utilities::trimRight(std::string& str) {
    std::string::size_type pos = str.find_last_not_of(" ");
    str.erase(pos + 1);
}

void utilities::trimLeft(std::string& str) {
    std::string::size_type pos = str.find_first_not_of(" ");
    str.erase(0, pos);
}

void utilities::trim(std::string& str) {
    trimRight(str);
    trimLeft(str);
}

int utilities::roundUp(int numToRound, int multiple) {
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