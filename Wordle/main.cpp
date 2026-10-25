#include <iostream>
#include <string>
#include <cctype>
#include <format>

constexpr std::size_t wordLength = 5;

enum class GuessStatus
{
	Valid,
	WordLengthError,
	InvalidCharacterError
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

void printGuess(const std::string& guess)
{
	for (char c : guess)
	{
		std::cout << "\x1b[30;42m" << ' ' << c << ' ' << "\x1b[0m" << ' ';
	}

	std::cout << '\n';
}


int main()
{
	std::string guess;

	GuessStatus result;

	do
	{
		std::cout << "Enter your guess: ";
		std::getline(std::cin, guess);

		result = validateGuess(guess);

		switch (result)
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
	while (result != GuessStatus::Valid);

	for (char& c : guess)
	{
		c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
	}

	printGuess(guess);

	return 0;
}