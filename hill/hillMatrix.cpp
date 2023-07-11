#include "hillMatrix.hpp"

HillMatrix::HillMatrix()
	: Matrix<int32_t>()
	, det_(-1)
{}

HillMatrix::HillMatrix(const size_t sizeOfSide)
	: Matrix<int32_t>(sizeOfSide)
	, det_(-1)
{}

HillMatrix::HillMatrix(const std::initializer_list<std::vector<int32_t>>& list)
	: Matrix<int32_t>(list)
	, det_(-1)
{
	if (list.size() != this->maxColsNumber(list)) {
		throw std::runtime_error("Matrix must be a square");
	}
}

HillMatrix::HillMatrix(const HillMatrix& m)
	: Matrix<int32_t>(m.sizeOfSides().first)
	, det_(-1)
{
	for (size_t i = 0; i < m.sizeOfSides().first; i++) {
		for (size_t j = 0; j < m.sizeOfSides().second; j++) {
			(*this)(i, j) = m(i, j);
		}
	}
}

HillMatrix HillMatrix::randomize(const int32_t size, const int32_t alphabetSize) {
	HillMatrix matrix{ this->sizeOfSides().first };
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			matrix(i, j) = Random<int>()(0, alphabetSize - 1);
		}
	}
	return matrix;
}

Digital HillMatrix::multiply(
	Digital digitalSeq,
	const Alphabet& alphabet
) {
	std::vector<int32_t> result{};

	size_t mod{ digitalSeq.size() % this->sizeOfSides().first };
	if (mod != 0) {
		std::string placeholders(this->sizeOfSides().first - mod, ' ');
		digitalSeq.concat(placeholders);
	}

	for (size_t k = 0; k < digitalSeq.size(); k += this->sizeOfSides().first) {
		for (size_t i = 0; i < this->sizeOfSides().first; i++) {
			int32_t swap{};
			for (size_t j = k, l = 0; l < this->sizeOfSides().second; j++, l++) {
				swap += digitalSeq[j] * (*this)(l, i);
			}
			result.push_back(modOf(swap, alphabet.size()));
		}
	}
	return Digital{ result, alphabet };
}

HillMatrix HillMatrix::minor(const int32_t row, const int32_t col) {
	int32_t markForRemove{ -1 };
	HillMatrix m{ *this };
	HillMatrix mnr{ m.sizeOfSides().first - 1 };

	for (size_t i = 0; i < m.sizeOfSides().first; i++) {
		m(row, i) = markForRemove;
		m(i, col) = markForRemove;
	}
	for (size_t i = 0; i < m.sizeOfSides().first; i++) {
		for (size_t j = 0; j < m.sizeOfSides().second; j++) {
			if (m(i, j) != markForRemove) {
				mnr.push(m(i, j));
			}
		}
	}
	return mnr;
}

// Need for memoization
int32_t HillMatrix::determinant() {
	const int32_t matrixSizeOfTwoOrder{ 2 * 2 };
	if (this->elementsQuantity() < matrixSizeOfTwoOrder) {
		return (*this)(0, 0);
	}
	if (det_ == -1) {
		if (this->elementsQuantity() == matrixSizeOfTwoOrder) {
			return twoOrderDeterminant(*this);
		}
		int32_t det{ 0 };
		int8_t sign{ 1 };
		for (size_t j = 0; j < this->sizeOfSides().first; j++) {
			det += (*this)(0, j) * this->minor(0, j).determinant() * sign;
			sign = sign == -1 ? 1 : -1;
		}
		det_ = det;
	}
	return det_;
}

HillMatrix HillMatrix::inverse(const int32_t alphabetSize) {
	HillMatrix invertMatrix{ this->sizeOfSides().first };
	int32_t keyDet{ this->determinant() }; // keyDet instead det_ ? fix it!
	int32_t invertKeyDet{ invertElemInRing(keyDet,  alphabetSize) };

	std::cout << keyDet << " : " << invertKeyDet << "\n";

	if (invertKeyDet == -1) {
		return HillMatrix{};
	}

	for (size_t i = 0; i < this->sizeOfSides().first; i++) {
		for (size_t j = 0; j < this->sizeOfSides().second; j++) {
			invertMatrix(j, i) =
				modOf(
					modOf(
						addon(
							this->minor(i, j).determinant(),
							i, j),
						alphabetSize) * invertKeyDet,
					alphabetSize);
			if (invertMatrix(j, i) < 0) {
				invertMatrix(j, i) += alphabetSize;
			}
		}
	}
	return invertMatrix;
}
