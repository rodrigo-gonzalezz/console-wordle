#include "Input.h"
#include "StringUtils.h"
#include "GameRules.h"

#include <iostream>
#include <format>


std::string readGuess()
{
	std::string guess;

	WordStatus status;

	do
	{
		std::cout << "Enter your guess: ";
		std::getline(std::cin, guess);

		guess = trim(guess);

		status = validateWord(guess);

		switch (status)
		{
		case WordStatus::Valid:
			break;
		case WordStatus::WordLengthError:
			std::cout << std::format("Guess should be a word {} characters long.\n", wordLength);
			break;
		case WordStatus::InvalidCharacterError:
			std::cout << "Guess should only contain letters.\n";
			break;
		}
	} while (status != WordStatus::Valid);

	toUpper(guess);

	return guess;
}