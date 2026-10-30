#pragma once

#include <string>
#include <vector>
#include <optional>

std::optional<std::vector<std::string>> readWords(const std::string& filePath);