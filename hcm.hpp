#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "hill/hillCipher.hpp"
#include "utilities/gcd/gcd.hpp"
#include "utilities/timer.hpp"
#include "argument/argument.hpp"

class Hcm {
public:
	Hcm(const HillCipher& hill, const Argument& arg);
    void start();
private:
    Argument arg_;
	HillCipher hillCipher_;
	std::fstream fileStream_;
};