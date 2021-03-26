#include "prime_gen.h"
#include<chrono>
#include <cmath>

const BigInt prime_gen::nextPrime(int length_in_bits){
	BigInt modulo = pow(BigInt(2), BigInt(length_in_bits), BigInt(0));
    BigInt result = modulo /  BigInt(2) + BigInt(1);
    BigInt minVal = result;
	srand(time(nullptr));
	while (!Cryptography::isPrime(result) || result < minVal) {
        int next_digit = rand();
		result = result + BigInt(next_digit);
		result = result % modulo;
	}
	return result;
}
const BigInt  prime_gen::next(int length_in_bits){



}
