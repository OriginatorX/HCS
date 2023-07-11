#include "gcd.hpp"

int32_t gcd(const int32_t a, const int32_t b) {
	return abs(b == 0 ? a : gcd(b, a % b));
}

Gcd gcdEx(const int32_t a, const int32_t b) {
	int32_t x{}, y{};
	if (a == 0) {
		x = 0; y = 1;
		return Gcd{ b, x, y };
	}
	Gcd d{ gcdEx(b % a, a) };
	x = d.y_ - (b / a) * d.x_;
	y = d.x_;
	return Gcd{ d.gcd_, x, y };
}

std::ostream& operator<<(std::ostream& stream, const Gcd& gcd) {
	stream
		<< "Devisor: " << gcd.gcd_
		<< " x: " << gcd.x_
		<< " y: " << gcd.y_ << "\n";
	return stream;
}

int32_t invertElemInRing(const int32_t a, const int32_t m) {
	Gcd g{ gcdEx(a, m) };
	return g.gcd_ != 1 ? -1 : (g.x_ % m + m) % m;
}
