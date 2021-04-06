#ifndef BIGINT_H
#define BIGINT_H

#endif // BIGINT_H_INCLUDED
#pragma once
#include <vector>
#include <cmath>
#include <string>
using namespace std;

class BigInt {
private:
    void removeLeadingZeros();
public:
    BigInt();
    BigInt(const string &s);
    BigInt(int n);
    BigInt(const vector<int> &bits, const bool &sign);
    bool sign = true; // >=0
    const static int base = 10;

    // base
    vector<int> bits = vector<int>(); // base10
    vector<int> bits2 = vector<int>(); // base2
    vector<int> bits64 = vector<int>();

    void toBase2();
    void toBase64();
    // -
    friend const BigInt operator - (const BigInt &a);

    //+ - * / % pow sqrt
    friend const BigInt operator + (const BigInt &a, const BigInt &b);
    friend const BigInt operator - (const BigInt &a, const BigInt &b);
    friend const BigInt operator * (const BigInt &a, const BigInt &b);
    friend const BigInt operator * (const BigInt &a, const int b);
    friend const BigInt operator / (const BigInt &a, const BigInt &b);
    friend const BigInt operator % (const BigInt &a, const BigInt &b);
    friend const BigInt pow(const BigInt &a, const BigInt &n, const BigInt& modulo);
    friend const BigInt sqrt(const BigInt &a);
    friend const BigInt abs(const BigInt &a);

    //> < == <= >= !=
    bool operator > (const BigInt &a) const;
    bool operator < (const BigInt &a) const;
    bool operator >= (const BigInt &a) const;
    bool operator <= (const BigInt &a) const;
    bool operator == (const BigInt &a) const;
    bool operator != (const BigInt &a) const;

    // output in console
    friend ostream &operator <<(ostream &out, const BigInt &a);
    friend istream &operator >>(istream &in, BigInt &a);

    static const BigInt random(const BigInt&);
};

const int findDigit(const BigInt& delta, const BigInt& num);
const BigInt gcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y);
const BigInt gcd(const BigInt& a, const BigInt& b);
const BigInt lcm(const BigInt& a, const BigInt& b);
bool congrEquation(const BigInt& a, const BigInt& b, const BigInt& m, vector<BigInt>& result);
const BigInt systemOfEquation(const vector<int> &r, const vector<int> &m);
int powModP(int a, int n, int p);


