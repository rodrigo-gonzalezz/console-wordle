#pragma once

#include "GameRules.h"

#include <string>
#include <array>


std::array<LetterState, wordLength> scoreGuess(const std::string& guess, const std::string& answer);