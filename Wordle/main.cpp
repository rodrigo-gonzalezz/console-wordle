#include <iostream>
#include <string>
#include <cctype>
#include <format>
#include <array>

constexpr std::size_t wordLength = 5;

enum class GuessStatus
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

GuessStatus validateGuess(const std::string& guess)
{
	if (guess.size() != wordLength) return GuessStatus::WordLengthError;

	for (char c : guess)
	{
		if (!std::isalpha(static_cast<unsigned char>(c))) return GuessStatus::InvalidCharacterError;
	}

	return GuessStatus::Valid;
}

std::array<LetterState, wordLength> scoreGuess(const std::string& guess, const std::string& answer)
{
	std::array<LetterState, wordLength> guessResult;

	for (std::size_t i = 0; i < wordLength; ++i)
	{
		if (guess[i] == answer[i])
		{
			guessResult[i] = LetterState::Correct;
		}
		else if (answer.find(guess[i]) != std::string::npos)
		{
			guessResult[i] = LetterState::Present;
		}
		else
		{
			guessResult[i] = LetterState::Absent;
		}
	}

	return guessResult;
}

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

	std::cout << '\n';
}


int main()
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
	} 
	while (status != GuessStatus::Valid);

	for (char& c : guess)
	{
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
	}

	const std::string answer = "CRANE";

	const std::array<LetterState, wordLength> guessResult = scoreGuess(guess, answer);

	printGuess(guess, guessResult);

	return 0;
}