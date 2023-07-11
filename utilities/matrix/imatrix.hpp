#pragma once

#include <cstdint>
#include <utility>
#include <ostream>

#define ABSTRACT

template <class T, class ty> ABSTRACT class IMatrix {
public:
	virtual ~IMatrix() = default;

	virtual inline ty& operator() (const size_t row, const size_t column) 				= 0;
	virtual T push(const ty& elem) 														= 0;
	virtual T deleteItem(const size_t row, const size_t col) 							= 0;
	virtual T fillBy(const ty& elem) 													= 0;
	virtual inline const ty& operator() (const size_t row, const size_t column) const 	= 0;
	virtual const std::pair<size_t, size_t> sizeOfSides() const 						= 0;
	virtual const size_t elementsQuantity() const 										= 0;
};
