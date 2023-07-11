#include "utils.hpp"
#include <cmath>

int32_t modOf(const int32_t number, const int32_t alphabetSize) {
	return number % alphabetSize;
}

int32_t twoOrderDeterminant(const Matrix<int32_t>& matrix) {
	return (matrix(0, 0) * matrix(1, 1)) - (matrix(0, 1) * matrix(1, 0));
}

int32_t addon(const int32_t elem, const int32_t i, const int32_t j) {
	return pow(-1, (i + 1) + (j + 1)) * elem;
}
