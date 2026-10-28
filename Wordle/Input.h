#pragma once

#include <string>


enum class GuessStatus
{
	Valid,
	WordLengthError,
	InvalidCharacterError
};

GuessStatus validateGuess(const std::string& guess);

std::string readGuess();