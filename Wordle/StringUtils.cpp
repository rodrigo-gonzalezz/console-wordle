#include "StringUtils.h"

#include <cctype>


std::string trim(const std::string& text)
{
	const std::string whitespace = " \t\r\n";

	const std::size_t first = text.find_first_not_of(whitespace);

	if (first == std::string::npos) return "";

	const std::size_t last = text.find_last_not_of(whitespace);

	const std::size_t length = last - first + 1;

	return text.substr(first, length);
}

void toUpper(std::string& text)
{
	for (char& c : text)
	{
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
	}
}