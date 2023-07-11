#pragma once

#include <cstdint>
#include <vector>

enum class lang {
	en = 0,
	ru = 1
};

struct Symbols {
	uint8_t start;
	uint8_t end;
	std::vector<char> additional;
};

Symbols defineLang(lang lMode, const std::vector<char>& addSymbols);
