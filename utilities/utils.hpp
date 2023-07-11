#pragma once

#include <cstdint>
#include "../utilities/matrix/matrix.hpp"

int32_t modOf(const int32_t number, const int32_t alphabetSize);
int32_t twoOrderDeterminant(const Matrix<int32_t>& matrix);
int32_t addon(const int32_t elem, const int32_t i, const int32_t j);
