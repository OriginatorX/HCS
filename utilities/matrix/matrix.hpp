#pragma once
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <ostream>
#include <initializer_list>

#include "iMatrix.hpp"

template <class T> class Matrix : public ABSTRACT IMatrix<Matrix<T>, T> {
public:
	Matrix();
	Matrix(const size_t rows, const size_t cols);
	Matrix(const size_t sideSize);
	Matrix(const std::initializer_list<std::vector<T>>& list);

	virtual inline T& operator() (const size_t row, const size_t col) override;
	virtual Matrix push(const T& elem) override;
	virtual Matrix deleteItem(const size_t row, const size_t col) override;
	virtual Matrix fillBy(const T& elem) override;

	virtual inline const T& operator() (const size_t row, const size_t col) const override;
	virtual const std::pair<size_t, size_t> sizeOfSides() const override;
	virtual const size_t elementsQuantity() const override;

	template <typename U>
	friend bool operator==(const Matrix<U>& first, const Matrix<U>& second);
	template <typename U>
	friend std::ostream& operator<<(std::ostream& stream, const Matrix<U>& m);

protected:
	void outOfBoundCheck(const size_t row, const size_t col) const;
	int64_t maxColsNumber(const std::initializer_list<std::vector<T>>& list);
private:
	size_t rows_;
	size_t cols_;
	std::vector<T> store_;
};

// Template class methods implementation

template <class T>
Matrix<T>::Matrix()
	: rows_(0)
	, cols_(0)
{}

template <class T>
Matrix<T>::Matrix(const size_t rows, const size_t cols)
	: rows_(rows)
	, cols_(cols)
	, store_(rows * cols)
{}

template <class T>
Matrix<T>::Matrix(const size_t sideSize)
	: rows_(sideSize)
	, cols_(sideSize)
	, store_(pow(sideSize, 2))
{}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::vector<T>>& list)
	: rows_(list.size())
	, cols_(maxColsNumber(list))
{
	for (const std::vector<T>& v : list) {
		std::vector<T> buff{v};
		if (buff.size() < cols_) {
			std::vector<T> fillers(cols_ - buff.size(), T{});
			buff.insert(buff.end(), fillers.begin(), fillers.end());
		}
		store_.insert(store_.end(), buff.begin(), buff.end());
	}
}

template <class T>
inline T& Matrix<T>::operator()(const size_t row, const size_t col) {
	outOfBoundCheck(row, col);
	return store_[(cols_ * row) + col];
}

template<class T>
inline Matrix<T> Matrix<T>::push(const T& elem) {
	for (size_t i = 0; i < rows_; i++) {
		for (size_t j = 0; j < cols_; j++) {
			if ((*this)(i, j) == 0) {
				(*this)(i, j) = elem;
				return *this;
			}
		}
	}
	store_.push_back(elem);
	std::vector<T> fillers(cols_ - 1, NULL); // cols_ == 0 for new empty matrix
	store_.insert(store_.end(), fillers.begin(), fillers.end());
	rows_++;
	return *this;
}

template <class T>
inline const T& Matrix<T>::operator()(const size_t row, const size_t col) const {
	outOfBoundCheck(row, col);
	return store_[(cols_ * row) + col];
}

template <class T>
Matrix<T> Matrix<T>::fillBy(const T& elem) {
	std::fill(store_.begin(), store_.end(), elem);
	return *this;
}

template <class T>
const std::pair<size_t, size_t> Matrix<T>::sizeOfSides() const {
	return { rows_, cols_ };
}

template <class T>
const size_t Matrix<T>::elementsQuantity() const {
	return store_.size();
}

template <class T>
Matrix<T> Matrix<T>::deleteItem(const size_t row, const size_t col) {
	outOfBoundCheck(row, col);
	auto removing = store_.begin() + (cols_ * row) + col;
	store_.erase(removing, removing + 1);
	store_.insert(store_.begin() + (cols_ * row) + cols_ - 1, {T{}});
	return *this;
}

template <typename U>
bool operator==(const Matrix<U>& first, const Matrix<U>& second) {
	if (first.elementsQuantity() != second.elementsQuantity()) {
		return false;
	}
	for (size_t i = 0; i < first.sizeOfSides().first; i++) {
		for (size_t j = 0; j < first.sizeOfSides().second; j++) {
			if (first(i, j) != second(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template <typename U>
std::ostream& operator<<(std::ostream& stream, const Matrix<U>& m) {
	for (size_t i = 0; i < m.sizeOfSides().first; i++) {
		for (size_t j = 0; j < m.sizeOfSides().second; j++) {
			stream << m(i, j) << " ";
		}
		stream << "\n";
	}
	return stream;
}

template <class T>
void Matrix<T>::outOfBoundCheck(const size_t row, const size_t col) const {
	if (row > rows_ - 1 || col > cols_ - 1) {
		throw std::runtime_error("Out of bounds");
	}
}

template <class T>
int64_t  Matrix<T>::maxColsNumber(const std::initializer_list<std::vector<T>>& list) {
	int64_t size{};
	for (const std::vector<T>& v : list) {
		if (v.size() > size) {
			size = static_cast<int64_t>(v.size());
		}
	}
	return size;
}
