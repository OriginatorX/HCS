#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

#include "../utilities/matrix/matrix.hpp"
#include "../utilities/random.hpp"
#include "../alphabet/alphabet.hpp"
#include "../digital/digital.hpp"
#include "../utilities/gcd/gcd.hpp"
#include "../utilities/utils.hpp"

class HillMatrix : public Matrix<int32_t> {
public:
	HillMatrix();
	explicit HillMatrix(const size_t sizeOfSide);
	HillMatrix(const std::initializer_list<std::vector<int32_t>>& list);

	HillMatrix(const HillMatrix&);
	//HillMatrix operator=(const HillMatrix&) = delete;

	HillMatrix randomize(const int32_t size, const int32_t alphabetSize);
	Digital multiply(
		Digital digitalSeq,
		const Alphabet& alphabet
	);
	HillMatrix minor(const int32_t row, const int32_t col);
	int32_t determinant();
	HillMatrix inverse(const int32_t alphabetSize);

private:
	int32_t det_;
};
