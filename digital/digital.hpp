#pragma once

#include <map>
#include <string>
#include <vector>
#include <ostream>

#include "../alphabet/alphabet.hpp"
#include "../utilities/matrix/matrix.hpp"

class Digital {
public:
	Digital();
	Digital(const std::string& str, const Alphabet& alphabet);
	Digital(const std::vector<int32_t>& digitalSeq, const Alphabet& alphabet);

	int32_t operator[](const size_t i);
	void concat(const std::string& str);

	const int32_t operator[](const size_t i) const;
	const size_t size() const;
	const std::string str() const;
	friend std::ostream& operator<<(std::ostream& stream, const Digital& digit);

private:
	std::string str_;
	std::vector<int32_t> digitized_;
	Alphabet alphabet_;
};
