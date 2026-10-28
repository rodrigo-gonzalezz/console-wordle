#include "Score.h"


constexpr char usedLetter = '_';

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