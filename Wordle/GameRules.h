#pragma once

#include <cstddef>

constexpr std::size_t wordLength = 5;
constexpr std::size_t maxAttempts = 6;

enum class LetterState
{
	Correct,
	Present,
	Absent
};