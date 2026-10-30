#include "GameRules.h"

#include <cctype>


WordStatus validateWord(const std::string& word)
{
	if (word.size() != wordLength) return WordStatus::WordLengthError;

	for (char c : word)
	{
		if (!std::isalpha(static_cast<unsigned char>(c))) return WordStatus::InvalidCharacterError;
	}

	return WordStatus::Valid;
}