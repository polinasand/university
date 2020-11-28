#pragma once
#include "BigInt/BigInt.h"
#include<iostream>
#include<map>
using namespace std;

class Cryptography {
private:
    // number is prime with probability 1 - 4^(1-N)
    static const int N = 20;
public:
    static const BigInt euler(const BigInt&);
    static const int mobius(const BigInt&);
    static const int legendre(const BigInt&, const BigInt&);
    static const int jacobi(const BigInt&, const BigInt&);
    static const bool isPrime(const BigInt&);
    static const BigInt discrete_log(const BigInt&, const BigInt&, const BigInt&);
    static const BigInt discrete_sqrt(const BigInt&, const BigInt&);
    static const void factor(const BigInt&, map<BigInt, int>&);
    static const BigInt inverseEl(const BigInt&, const BigInt&);
    static const BigInt factorLenstra(const BigInt&);
};
