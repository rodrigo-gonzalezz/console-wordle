#include "WordList.h"
#include "GameRules.h"
#include "StringUtils.h"

#include <fstream>


std::optional<std::vector<std::string>> readWords(const std::string& filePath)
{
	std::vector<std::string> words;

	std::ifstream file(filePath);

	if (!file) return std::nullopt;

	std::string line;

	while (std::getline(file, line))
	{
		line = trim(line);
		const WordStatus status = validateWord(line);

		if (status != WordStatus::Valid) continue;

		toUpper(line);
		words.push_back(line);
	}

	return words;
}