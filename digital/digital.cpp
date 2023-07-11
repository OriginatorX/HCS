#include "digital.hpp"
#include "../utilities/utils.hpp"

Digital::Digital()
	: str_("")
	, alphabet_(Alphabet(lang::en))
{}

Digital::Digital(const std::string& str, const Alphabet& alphabet)
	: str_(str)
	, alphabet_(alphabet)
{
	for (char c : str) {
		for (const auto& [key, value] : alphabet_.items()) {
			if (c == key) {
				digitized_.push_back(value);
			}
		}
	}
}

Digital::Digital(const std::vector<int32_t>& digitalSeq, const Alphabet& alphabet)
	: digitized_(digitalSeq)
	, alphabet_(alphabet)
{
	for (int32_t i : digitalSeq) {
		for (const auto& [key, value] : alphabet_.items()) {
			if (i == value) {
				str_.push_back(key);
			}
		}
	}
}

int32_t Digital::operator[](const size_t i) {
	return digitized_[i];
}

void Digital::concat(const std::string& str) {
	Digital digitalSeq(str, alphabet_);
	for (size_t i = 0; i < digitalSeq.size(); i++) {
		digitized_.push_back(digitalSeq[i]);
	}
}

const size_t Digital::size() const {
	return digitized_.size();
}

const std::string Digital::str() const {
	return str_;
}

const int32_t Digital::operator[](const size_t i) const {
	return digitized_[i];
}

std::ostream& operator<<(std::ostream& stream, const Digital& digit) {
	for (size_t i = 0; i < digit.size(); i++) {
		stream << digit[i];
	}
	return stream;
}
