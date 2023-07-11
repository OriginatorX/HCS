#include "alphabet.hpp"

Alphabet::Alphabet(lang lMode, const std::vector<char>& additionalSymbols)
	: symbols_(defineLang(lMode, additionalSymbols))
	, alphabet_()
{
	for (int16_t c = symbols_.start, i = 0; c <= symbols_.end; c++, i++) {
		alphabet_.insert({ c, static_cast<size_t>(i) });
	}
	if (!symbols_.additional.empty()) {
		addSymbols(this);
	}
}

const std::map<char, size_t> Alphabet::items() const {
	return alphabet_;
}

const size_t Alphabet::size() const {
	return alphabet_.size();
}

void addSymbols(Alphabet* a) {
	size_t i { a->alphabet_.size() };
	for (const auto& sym : a->symbols_.additional) {
		a->alphabet_.insert({ sym, i++ });
	}
}

Symbols defineLang(lang lMode, const std::vector<char>& addSymbols) {
	return (
        lMode == lang::en
            ? Symbols{ 32, 126, addSymbols } 
            : Symbols{ 128, 255, { ' ', '.', ',' } }
    );
}
