#include <iostream>
#include "hill/hillCipher.hpp"
#include "utilities/timer.hpp"
#include "argument/argument.hpp"
#include "hcm.hpp"

int main(int argc, const char** argv) {
	Hcm{
		HillCipher{
			HillMatrix{
				{  6,24, 1 },
				{ 13,16,10 },
				{ 20,17, 3 },
			}, 
			lang::en
		},
		Argument{ argc, argv }
	}.start();
	return EXIT_SUCCESS;
}
