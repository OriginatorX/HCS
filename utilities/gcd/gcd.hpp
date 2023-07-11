#pragma once

#include <ostream>

struct Gcd {
	int32_t gcd_;
	int32_t x_;
	int32_t y_;

	friend std::ostream& operator<<(std::ostream& stream, const Gcd& gcd);
};

int32_t gcd(const int32_t a, const int32_t b);
Gcd gcdEx(const int32_t a, const int32_t b);
std::ostream& operator<<(std::ostream& stream, const Gcd& gcd);
int32_t invertElemInRing(const int32_t a, const int32_t m);
