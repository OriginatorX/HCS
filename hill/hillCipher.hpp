#pragma once

#include <string>
#include <map>

#include "hillMatrix.hpp"
#include "../digital/digital.hpp"
#include "../alphabet/alphabet.hpp"
#include "../utilities/utils.hpp"

class HillCipher {
public:
	//HillCipher(const size_t sizeOfKey, lang lMode);
	HillCipher(const HillMatrix& key, lang lMode);

	std::string encrypt(const std::string& text);
	std::string decrypt(const std::string& cipher);

private:
	Alphabet alphabet_;
	Digital digitalText_;
	Digital digitalCipher_;
	HillMatrix key_;
	HillMatrix invertKey_;
};
