#pragma once

#include <map>
#include <vector>

#include "symbols.hpp"

class Alphabet {
public:
	Alphabet(
		lang lMode, 
		const std::vector<char>& additionalSymbols = {}
	);
	const std::map<char, size_t> items() const;
	const size_t size() const;
private:
	friend void addSymbols(Alphabet* alphabet);
private:
	Symbols symbols_;
	std::map<char, size_t> alphabet_;
};

