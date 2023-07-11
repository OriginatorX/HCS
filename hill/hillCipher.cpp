#include <map>
#include <sstream>
#include "hillCipher.hpp"
#include "../utilities/random.hpp"
#include "../utilities/gcd/gcd.hpp"
#include "../alphabet/alphabet.hpp"
#include "hillMatrix.hpp"

/*HillCipher::HillCipher(const size_t sizeOfKey, lang lMode)
	: alphabet_{ lMode }
	, digitalText_{}
	, digitalCipher_{}
	, key_{ sizeOfKey }
{
	bool keep{ true };
	while (keep) {
		key_ = std::move(key_.randomize(sizeOfKey, alphabet_.size()));
		invertKey_ = std::move(key_.inverse(alphabet_.size()));
		keep = invertKey_.elementsQuantity() != 0 ? false : true;
	}
}*/

HillCipher::HillCipher(const HillMatrix& key, lang lMode)
	: alphabet_{ lMode }
	, digitalCipher_{}
	, digitalText_{}
	, key_{ key }
{
	invertKey_ = std::move(key_.inverse(alphabet_.size()));;
	if (invertKey_.elementsQuantity() == 0) {
		throw std::runtime_error("Got matrix key is not valid");
	}
}

std::string HillCipher::encrypt(const std::string& text) {
	digitalText_ = Digital{text, alphabet_};
	return key_.multiply(digitalText_, alphabet_).str();
}

std::string HillCipher::decrypt(const std::string& cipher) {
	digitalCipher_ = Digital{cipher, alphabet_};
	return invertKey_.multiply(digitalCipher_, alphabet_).str();
}
