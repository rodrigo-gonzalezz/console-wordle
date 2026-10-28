#include <iostream>
#include <string>
#include <cctype>
#include <format>
#include <array>

constexpr std::size_t wordLength = 5;

constexpr std::size_t maxAttempts = 6;

constexpr char usedLetter = '_';

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

	guessResult.fill(LetterState::Absent);

	std::string letterPool = answer;

	for (std::size_t i = 0; i < wordLength; ++i)
	{
		if (guess[i] == answer[i])
		{
			guessResult[i] = LetterState::Correct;
			letterPool[i] = usedLetter;
		}
	}

	for (std::size_t i = 0; i < wordLength; ++i)
	{
		if (guessResult[i] != LetterState::Correct)
		{
			const std::size_t position = letterPool.find(guess[i]);

			if (position != std::string::npos)
			{
				guessResult[i] = LetterState::Present;
				letterPool[position] = usedLetter;
			}	
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

	std::cout << "\n\n";
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


int main()
{
	const std::string answer = "CRANE";

	bool guessedCorrectly = false;

	for (std::size_t attempt = 0; attempt < maxAttempts; ++attempt)
	{
		std::cout << "Attempt " << attempt + 1 << '/' << maxAttempts << '\n';

		const std::string guess = readGuess();

		const std::array<LetterState, wordLength> guessResult = scoreGuess(guess, answer);

		printGuess(guess, guessResult);

		if (guess == answer)
		{
			guessedCorrectly = true;

			if (attempt == 0) std::cout << "That is correct, great job! You got it on the first try!\n"; 
			else std::cout << "That is correct, great job! You got it in " << attempt + 1 << " tries!\n";

			break;
		}
	}

	if (!guessedCorrectly)
	{
		std::cout << "That was close, better luck next time! The answer was: " << answer << '\n';
	}

	return 0;
}