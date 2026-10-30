#include "WordList.h"

#include <fstream>


std::optional<std::vector<std::string>> readWords(const std::string& filePath)
{
	std::vector<std::string> words;

	std::ifstream file(filePath);

	if (!file) return std::nullopt;

	std::string line;

	while (std::getline(file, line))
	{
		words.push_back(line);
	}

	return words;
}