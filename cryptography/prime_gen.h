#pragma once
#include "Cryptography.h"

class prime_gen {
private:
public:
	static const BigInt nextPrime(int length_in_bits);
	static const BigInt next(int length_in_bits);
};
