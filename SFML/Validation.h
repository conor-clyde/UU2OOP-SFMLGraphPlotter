#include <string>

namespace utilities {
	bool ValidLength(std::string txt, int min, int max);
	bool ValidLetterNumberWhitespace(std::string txt);
	std::string ValidLetterNumber(std::string txt);
	bool ValidNumber(std::string txt);
	char ValidYN(std::string msg);
	int ValidRangeInt(std::string msg, int min, int max);
}