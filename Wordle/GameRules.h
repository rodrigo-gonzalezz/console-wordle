#pragma once

#include <cstddef>
#include <string>

constexpr std::size_t wordLength = 5;
constexpr std::size_t maxAttempts = 6;

enum class WordStatus
{
	Valid,
	WordLengthError,
	InvalidCharacterError
};

enum class LetterState
{
	Correct,
	Present,
	Absent
};

WordStatus validateWord(const std::string& word);