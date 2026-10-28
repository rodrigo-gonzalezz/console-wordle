#include "Display.h"

#include <iostream>

void printGuess(const std::string& guess, const std::array<LetterState, wordLength>& guessResult)
{
	for (std::size_t i = 0; i < wordLength; ++i)
	{
		std::string colorCode;

		switch (guessResult[i])
		{
		case LetterState::Correct:
			colorCode = "\x1b[30;42m";
			break;
		case LetterState::Present:
			colorCode = "\x1b[30;43m";
			break;
		case LetterState::Absent:
			colorCode = "\x1b[30;100m";
			break;
		}

		std::cout << colorCode << ' ' << guess[i] << ' ' << "\x1b[0m" << ' ';
	}

	std::cout << "\n\n";
}