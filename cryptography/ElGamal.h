#pragma once
#include "BigInt/BigInt.h"
#include "Cryptography.h"
#include<iostream>
using namespace std;

struct Point {
    BigInt x = BigInt(0);
    BigInt y = BigInt(0);
    bool zero = false;
    Point(BigInt _x, BigInt _y, bool _zero) {
        x = _x;
        y = _y;
        zero = _zero;
    }
};

struct curve {
    BigInt a;
    BigInt b;
    BigInt n;
    curve(BigInt _a, BigInt _b, BigInt _n) {
        a = _a;
        b = _b;
        n = _n;
    }
};

class ElGamal {
private:
    /*static const curve e = curve(BigInt(0), BigInt(7), BigInt("1461501637330902918203684832716283019651637554291"));
    static Point P = Point(BigInt("1774985273"),
                           Cryptography::discrete_sqrt(
                                (pow(BigInt("1774985273"), BigInt(3), e.n) + e.a*BigInt("1774985273") + e.b) % e.n, e.n), false);
    Static BigInt N = BigInt("1461501637330902918203684832716283019651637554291");*/
public:
    ElGamal();
    static const Point add(const Point&, const Point&, const curve&);
    static const void elGamal();
};
