#include "Input.h"
#include "GameRules.h"

#include <iostream>
#include <format>
#include <cctype>


GuessStatus validateGuess(const std::string& guess)
{
	if (guess.size() != wordLength) return GuessStatus::WordLengthError;

	for (char c : guess)
	{
		if (!std::isalpha(static_cast<unsigned char>(c))) return GuessStatus::InvalidCharacterError;
	}

	return GuessStatus::Valid;
}

std::string readGuess()
{
	std::string guess;

	GuessStatus status;

	do
	{
		std::cout << "Enter your guess: ";
		std::getline(std::cin, guess);

		status = validateGuess(guess);

		switch (status)
		{
		case GuessStatus::Valid:
			break;
		case GuessStatus::WordLengthError:
			std::cout << std::format("Guess should be a word {} characters long.\n", wordLength);
			break;
		case GuessStatus::InvalidCharacterError:
			std::cout << "Guess should only contain letters.\n";
			break;
		}
	} while (status != GuessStatus::Valid);

	for (char& c : guess)
	{
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
	}

	return guess;
}